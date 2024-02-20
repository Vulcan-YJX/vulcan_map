#include "vulcan_map/vulcan_map_node.hpp"

void VulcanMap::callback(const geometry_msgs::msg::PoseStamped::SharedPtr pose, const sensor_msgs::msg::PointCloud2::SharedPtr cloud)
{
    // Transform PointCloud with Pose.
    double data[7] = {pose->pose.position.x, pose->pose.position.y, pose->pose.position.z, pose->pose.orientation.w,
                   pose->pose.orientation.x, pose->pose.orientation.y, pose->pose.orientation.z};
    Eigen::Quaterniond q(data[3], data[4], data[5], data[6]);
    T = Eigen::Isometry3d(q);
    T.pretranslate(Eigen::Vector3d(data[0], data[1], data[2]));    
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*cloud, *pcl_cloud);
    pcl::transformPointCloud(*pcl_cloud, *pcl_cloud, T.matrix());

    RCLCPP_INFO(this->get_logger(),"PointCloud size: %lu",pcl_cloud->size());

    if(pcl_cloud->size() > per_frame_size){
        *global_map += *pcl_cloud;
    }
    vulcan_pcl::voxel_grid(global_map,0.05);
    double limited_queue[6] = {data[0]-1.5,data[0]+1.5,data[1]-1.5,data[1]+1.5,data[2]-1.5,data[2]+1.5};
    vulcan_pcl::pass_through_box(global_map,local_map,limited_queue);
    
    auto header_msg = std::make_unique<std_msgs::msg::Header>();
    auto local_msg = std::make_unique<sensor_msgs::msg::PointCloud2>();
    pcl::toROSMsg(*local_map, *local_msg);
    header_msg->stamp = this->now();
    header_msg->frame_id = "map";
    local_msg->header = *header_msg;
    local_publisher_->publish(std::move(local_msg));

    auto global_msg = std::make_unique<sensor_msgs::msg::PointCloud2>();
    pcl::toROSMsg(*global_map, *global_msg);
    global_msg->header = *header_msg;
    global_publisher_->publish(std::move(global_msg));
}
