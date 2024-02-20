cmake_minimum_required(VERSION 3.5)
project(vulcan_map)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)


include_directories(
  include
  ${PCL_INCLUDE_DIRS}
)

ament_auto_add_library(${PROJECT_NAME}_lib SHARED
  src/vulcan_map_node.cpp
  src/pcl_tools.cpp
)
target_link_libraries(${PROJECT_NAME}_lib ${PCL_LIBRARIES})

ament_auto_add_executable(${PROJECT_NAME} src/main.cpp)
# ament_target_dependencies(${PROJECT_NAME} rclcpp sensor_msgs geometry_msgs message_filters)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

install(TARGETS
  ${PROJECT_NAME} 
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  ${PROJECT_NAME}_lib
  LIBRARY DESTINATION lib
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()