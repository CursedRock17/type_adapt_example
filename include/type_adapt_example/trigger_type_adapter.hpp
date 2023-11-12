#include <string>
#include <memory>

#include "rclcpp/type_adapter.hpp"
#include "std_srvs/srv/trigger.hpp"

struct CustomTrigger
{
  struct TriggerResponse
  {
    bool success;
    std::string message;
  };
  struct Empty {};

  using Request = Empty;
  using Response = TriggerResponse;

};

template<>
struct rclcpp::TypeAdapter<CustomTrigger, std_srvs::srv::Trigger>
{
  using is_specialized = std::true_type;
  using custom_type = CustomTrigger;
  using ros_message_type = std_srvs::srv::Trigger;

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


