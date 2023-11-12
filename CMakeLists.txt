cmake_minimum_required(VERSION 3.8)
project(type_adapt_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_srvs REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(rclcpp REQUIRED)

set(NODE_HEADERS
  include/type_adapt_example/set_bool_node.hpp
  include/type_adapt_example/add_diagnostics_node.hpp
  include/type_adapt_example/empty_node.hpp
  include/type_adapt_example/trigger_node.hpp
  include/type_adapt_example/change_state_node.hpp
  include/type_adapt_example/get_state_node.hpp
)

add_executable(server_node_process src/server_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(server_node_process rclcpp std_srvs diagnostic_msgs lifecycle_msgs)
target_include_directories(server_node_process PUBLIC include)

add_executable(client_node_process src/client_node_process.cpp "${NODE_HEADERS}")
ament_target_dependencies(client_node_process rclcpp std_srvs diagnostic_msgs lifecycle_msgs)
target_include_directories(client_node_process PUBLIC include)

install(TARGETS
server_node_process
client_node_process
DESTINATION lib/${PROJECT_NAME})

ament_package()
