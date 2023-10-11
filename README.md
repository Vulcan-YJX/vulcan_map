<p align="center"><strong>Vulcan_Map</strong></p>
<p align="center"><a href="https://github.com/Vulcan-YJX/vulcan_map/blob/main/LICENSE"><img alt="License" src="https://img.shields.io/badge/License-LGPL%202.1-orange"/></a>
<img alt="language" src="https://img.shields.io/badge/language-c++-red"/>
<img alt="platform" src="https://img.shields.io/badge/platform-linux-l"/>
</p>

<p align="center">
    语言：<a href="README.en.md"><strong>English</strong></a> / <strong>中文</strong>
</p>

​	基于订阅 **Pose** 与 **PointCloud2** 的数据，用于生成导航所需的局部稠密点云地图和局部点云地图。

------

#### ROS Topics Published

| ROS Topic                | Interface                                                    | Description                                    |
| ------------------------ | ------------------------------------------------------------ | ---------------------------------------------- |
| `local_map/point_cloud`  | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | 局部地图，基于全局地图于pose                   |
| `global_map/point_cloud` | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | 全局地图，地图基于 pose 信息和输入的点云生成。 |


#### ROS Topics Subscribed 

| ROS Topic           | Interface                                                    | Description                                          |
| ------------------- | ------------------------------------------------------------ | ---------------------------------------------------- |
| `dummy/pose`        | [`geometry_msgs/PoseStamped`](https://github.com/ros2/common_interfaces/blob/humble/geometry_msgs/msg/PoseStamped.msg) | 模拟位姿的输出，绘制一个边长为5m的正方形。           |
| `dummy/point_cloud` | [`sensor_msgs/PointCloud2`](https://github.com/ros2/common_interfaces/blob/humble/sensor_msgs/msg/PointCloud2.msg) | 模拟点云输出，绘制一个 z 为一米的边长为1米的点云块。 |

