#include <rclcpp/rclcpp.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include "std_msgs/msg/header.hpp"
#include "vulcan_map/pcl_tools.hpp"
#include "pcl/common/transforms.h"
#include <pcl_conversions/pcl_conversions.h>


class VulcanMap : public rclcpp::Node
{
public:
  VulcanMap() : Node("vulcan_map_node")
  {
    pose_sub_.subscribe(this, "dummy/pose");
    cloud_sub_.subscribe(this, "dummy/point_cloud");
    RCLCPP_INFO(this->get_logger(), "Received pose and cloud");
    sync_ = std::make_shared<message_filters::Synchronizer<MapSyncPolicy>>(MapSyncPolicy(5), pose_sub_, cloud_sub_);
    sync_->registerCallback(&VulcanMap::callback, this);
    T = Eigen::Isometry3d::Identity();

    // Map publisher init.
    local_map.reset(new pcl::PointCloud<pcl::PointXYZ>);
    global_map.reset(new pcl::PointCloud<pcl::PointXYZ>);
    local_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("local_map/point_cloud", 10);
    global_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("global_map/point_cloud", 10);
  }

public:
  int per_frame_size = 100;

private:
  
  void callback(const geometry_msgs::msg::PoseStamped::SharedPtr pose,
                const sensor_msgs::msg::PointCloud2::SharedPtr cloud);

  // ApproximateTime  
  typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::msg::PoseStamped, sensor_msgs::msg::PointCloud2> MapSyncPolicy;
  message_filters::Subscriber<geometry_msgs::msg::PoseStamped> pose_sub_;
  message_filters::Subscriber<sensor_msgs::msg::PointCloud2> cloud_sub_;
  std::shared_ptr<message_filters::Synchronizer<MapSyncPolicy>> sync_;
  
  // Map init
  Eigen::Isometry3d T;
  pcl::PointCloud<pcl::PointXYZ>::Ptr local_map;
  pcl::PointCloud<pcl::PointXYZ>::Ptr global_map;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr local_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr global_publisher_;

};
