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
find_package(rclcpp REQUIRED)

add_executable(server src/service_server.cpp include/type_adapt_example/set_bool_type_adapter.hpp)
ament_target_dependencies(server rclcpp std_srvs)
target_include_directories(server PUBLIC include)

add_executable(client src/service_client.cpp include/${PROJECT_NAME}/set_bool_type_adapter.hpp)
ament_target_dependencies(client rclcpp std_srvs)
target_include_directories(client PUBLIC include)

install(TARGETS
server
client
DESTINATION lib/${PROJECT_NAME})

ament_package()
