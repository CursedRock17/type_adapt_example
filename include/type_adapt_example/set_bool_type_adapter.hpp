#include <string>
#include <memory>

#include "rclcpp/type_adapter.hpp"
#include "std_srvs/srv/set_bool.hpp"

struct CustomBool
{
  struct SetBoolResponse
  {
    bool success;
    std::string message;
  };
  bool data;

  using Request = bool;
  using Response = SetBoolResponse;

};

template<>
struct rclcpp::TypeAdapter<CustomBool, std_srvs::srv::SetBool>
{
  using is_specialized = std::true_type;
  using custom_type = CustomBool;
  using ros_message_type = std_srvs::srv::SetBool;

  static void
  convert_to_ros_service_request(
    const custom_type::Request & source,
    ros_message_type::Request & destination)
  {
    destination.data = source;
  }

  static void
  convert_to_custom_service_request(
    const ros_message_type::Request & source,
    custom_type::Request & destination)
  {
    destination = source.data;
  }

  static void
  convert_to_ros_service_response(
    const custom_type::Response & source,
    ros_message_type::Response & destination)
  {
    destination.success = source.success;
    destination.message = source.message;
  }

  static void
  convert_to_custom_service_response(
    const ros_message_type::Response & source,
    custom_type::Response & destination)
  {
    destination.success = source.success;
    destination.message = source.message;
  }
};


