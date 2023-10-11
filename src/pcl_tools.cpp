#include "vulcan_map/pcl_tools.hpp"

namespace vulcan_pcl
{

void voxel_grid(CloudPtr cloud, float voxel_size) {
    pcl::VoxelGrid<PointType> voxel;
    voxel.setLeafSize(voxel_size, voxel_size, voxel_size);
    voxel.setInputCloud(cloud);

    CloudPtr output(new PointCloudType);
    voxel.filter(*output);
    cloud->swap(*output);
}

void pass_through_box(CloudPtr incloud,CloudPtr outcloud,double* limited){
    pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(incloud);

    pass.setFilterFieldName("x");
    pass.setFilterLimits(limited[0],limited[1]);
    pass.filter(*temp_cloud);

    pass.setInputCloud(temp_cloud);
    pass.setFilterFieldName("y");
    pass.setFilterLimits(limited[2],limited[3]);
    pass.filter(*temp_cloud);

    pass.setInputCloud(temp_cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(limited[4], limited[5]);
    pass.filter(*outcloud);
}

}

