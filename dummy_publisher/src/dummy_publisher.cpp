#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

class DummyPub : public rclcpp::Node
{
public:
  DummyPub() : Node("dummy_publisher") , step_size_(0.03), side_length_(5.0), rate_(30)
  {
    // 创建发布者
    point_cloud_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("dummy/point_cloud", 10);
    pose_publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("dummy/pose", 30);

    // 创建定时器
    point_cloud_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),  // 10 Hz
      std::bind(&DummyPub::publishPointCloud, this));
    
    pose_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(33),  // 30 Hz
      std::bind(&DummyPub::publishPose, this));

    generateSquarePath();
  }

private:

    void generateSquarePath()
    {
        int steps_per_side = side_length_ / step_size_;
        double angle_deg,angle_rad;  

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < steps_per_side; ++j)
            {
                geometry_msgs::msg::PoseStamped pose;
                // pose.header.stamp = this->now();
                pose.header.frame_id = "map";

                pose.pose.position.x = (i == 0) ? side_length_ : (i == 1 ? side_length_ - j * step_size_ : (i == 2 ? 0.0 : j * step_size_));
                pose.pose.position.y = (i == 0) ? j * step_size_ : (i == 1 ? side_length_ : (i == 2 ? side_length_ - j * step_size_ : 0.0));
                pose.pose.position.z = 0.0;

                angle_deg = i * 90.0;  
                angle_rad = angle_deg * M_PI / 180.0; 
                pose.pose.orientation.x = 0.0;
                pose.pose.orientation.y = 0.0;
                pose.pose.orientation.z = sin(angle_rad / 2.0);
                pose.pose.orientation.w = cos(angle_rad / 2.0);

                square_path_.push_back(pose);
            }
        }
    }
    
  void publishPointCloud()
  {
    auto point_cloud_msg = std::make_unique<sensor_msgs::msg::PointCloud2>();
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 创建一个 1m x 1m 的平面，点间隔为 0.01m
    for (float x = -0.5; x <= 0.5; x += 0.05) {
        for (float y = -0.5; y <= 0.5; y += 0.05) {
            pcl::PointXYZ point;
            point.x = x;
            point.y = y;
            point.z = 1.0;  // 1m 高
            cloud->points.push_back(point);
        }
    }

    cloud->width = cloud->points.size();
    cloud->height = 1;

    // sensor_msgs::msg::PointCloud2 point_cloud_msg;
    pcl::toROSMsg(*cloud, *point_cloud_msg);

    point_cloud_msg->header.stamp = this->now();
    point_cloud_msg->header.frame_id = "map";

    point_cloud_publisher_->publish(std::move(point_cloud_msg));
  }

    void publishPose()
    {
        if (!square_path_.empty())
        {
            auto pose = square_path_.front();
            square_path_.erase(square_path_.begin());
            RCLCPP_INFO(this->get_logger(), "Publishing pose: %.1f, %.1f", pose.pose.position.x, pose.pose.position.y);
            pose.header.stamp = this->now();
            pose_publisher_->publish(pose);
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_publisher_;
    std::vector<geometry_msgs::msg::PoseStamped> square_path_;
    double step_size_;
    double side_length_;
    double rate_;

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_publisher_;
  rclcpp::TimerBase::SharedPtr point_cloud_timer_;
  rclcpp::TimerBase::SharedPtr pose_timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DummyPub>());
  rclcpp::shutdown();
  return 0;
}