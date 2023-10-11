<p align="center"><strong>Vulcan_Map</strong></p>
<p align="center"><a href="https://github.com/Vulcan-YJX/vulcan_map/blob/main/LICENSE"><img alt="License" src="https://img.shields.io/badge/License-LGPL%202.1-orange"/></a>
<img alt="language" src="https://img.shields.io/badge/language-c++-red"/>
<img alt="platform" src="https://img.shields.io/badge/platform-linux-l"/>
</p>


<p align="center">
    语言：<a href="README.en.md"><strong>English</strong></a> / <strong>中文</strong>
</p>


Based on subscription data from  **Pose ** and **PointCloud2** , used to generate local dense point cloud maps and local point cloud maps required for navigation.

------

#### ROS Topics Published

| ROS Topic                | Interface                                                    | Description                                                  |
| ------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `local_map/point_cloud`  | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | Local map is base on global map and pose.                    |
| `global_map/point_cloud` | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | Global map, generated based on pose information and input point clouds. |


#### ROS Topics Subscribed 

| ROS Topic           | Interface                                                    | Description                                                  |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `dummy/pose`        | [`geometry_msgs/PoseStamped`](https://github.com/ros2/common_interfaces/blob/humble/geometry_msgs/msg/PoseStamped.msg) | Dummy pose draw a square. Side length is 5m.                 |
| `dummy/point_cloud` | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | Draw a point cloud block with a side length of 1 meter and z as one meter. |

