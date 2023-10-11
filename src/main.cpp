#include "vulcan_map/vulcan_map_node.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VulcanMap>());
  rclcpp::shutdown();
  return 0;
}