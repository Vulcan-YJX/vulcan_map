cmake_minimum_required(VERSION 3.5)
project(dummy_publisher)

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)

ament_auto_add_executable(dummy_publisher src/dummy_publisher.cpp)
target_link_libraries(dummy_publisher ${PCL_LIBRARIES})

# 设置 PCL 的编译定义和编译选项
target_compile_definitions(dummy_publisher PUBLIC ${PCL_DEFINITIONS})
target_include_directories(dummy_publisher PUBLIC ${PCL_INCLUDE_DIRS})
target_link_directories(dummy_publisher PUBLIC ${PCL_LIBRARY_DIRS})

install(TARGETS
  dummy_publisher
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
