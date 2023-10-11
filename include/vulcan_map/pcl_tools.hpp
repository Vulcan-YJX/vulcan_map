
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include "vulcan_map/point_types.h"

namespace vulcan_pcl
{

void voxel_grid(CloudPtr cloud, float voxel_size);

void pass_through_box(CloudPtr incloud,CloudPtr outcloud,double* limited);

}

