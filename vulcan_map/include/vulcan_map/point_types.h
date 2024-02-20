#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace vulcan_pcl {

using PointType = pcl::PointXYZ;
using PointCloudType = pcl::PointCloud<PointType>;    
using CloudPtr = PointCloudType::Ptr;

// using PointT = pcl::PointXYZ;
using PointNT = pcl::PointNormal;
using Normal = pcl::Normal;
using PointTC = pcl::PointXYZRGB;

// using PointCloudT = pcl::PointCloud<PointT>;
using PointCloudN = pcl::PointCloud<PointNT>;
using NormalCloud = pcl::PointCloud<Normal>;
using PointCloudC = pcl::PointCloud<PointTC>;

}