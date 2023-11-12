#include <string>
#include <memory>

#include "rclcpp/type_adapter.hpp"
#include "std_srvs/srv/empty.hpp"

struct CustomEmpty
{
  struct Empty {};
  using Request = Empty;
  using Response = Empty;
};

template<>
struct rclcpp::TypeAdapter<CustomEmpty, std_srvs::srv::Empty>
{
  using is_specialized = std::true_type;
  using custom_type = CustomEmpty;
  using ros_message_type = std_srvs::srv::Empty;

  static void
  convert_to_ros_service_request(
    const custom_type::Request & source,
    ros_message_type::Request & destination)
  {
    (void)source;
  }

  static void
  convert_to_custom_service_request(
    const ros_message_type::Request & source,
    custom_type::Request & destination)
  {
    (void)source;
  }

  static void
  convert_to_ros_service_response(
    const custom_type::Response & source,
    ros_message_type::Response & destination)
  {
    (void)source;
  }

  static void
  convert_to_custom_service_response(
    const ros_message_type::Response & source,
    custom_type::Response & destination)
  {
    (void)source;
  }
};


