cmake_minimum_required(VERSION 3.8)
project(type_adapt_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

set(NODE_HEADERS
  include/type_adapt_example/string_node.hpp
  include/type_adapt_example/typed_string_node.hpp
  include/type_adapt_example/string_type_adapter.hpp
)

add_executable(pub_node_process src/pub_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(pub_node_process rclcpp std_msgs )
target_include_directories(pub_node_process PUBLIC include)

add_executable(sub_node_process src/sub_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(sub_node_process rclcpp std_msgs )
target_include_directories(sub_node_process PUBLIC include)

add_executable(pub_type_adapt_node_process src/pub_type_adapt_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(pub_type_adapt_node_process rclcpp std_msgs )
target_include_directories(pub_type_adapt_node_process PUBLIC include)

add_executable(sub_type_adapt_node_process src/sub_type_adapt_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(sub_type_adapt_node_process rclcpp std_msgs )
target_include_directories(sub_type_adapt_node_process PUBLIC include)

install(TARGETS
pub_node_process
sub_node_process
pub_type_adapt_node_process
sub_type_adapt_node_process
DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
