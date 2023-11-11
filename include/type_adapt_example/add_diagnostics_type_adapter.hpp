#include <memory>
#include <string>

#include "rclcpp/type_adapter.hpp"
#include "diagnostic_msgs/srv/add_diagnostics.hpp"

struct CustomAddDiagnostics
{
  struct AddDiagnosticsResponse
  {
    bool success;
    std::string message;
  };
  std::string load_namespace;

  using Request = std::string;
  using Response = AddDiagnosticsResponse;

};

template<>
struct rclcpp::TypeAdapter<CustomAddDiagnostics, diagnostic_msgs::srv::AddDiagnostics>
{
  using is_specialized = std::true_type;
  using custom_type = CustomAddDiagnostics;
  using ros_message_type = diagnostic_msgs::srv::AddDiagnostics;

  static void
  convert_to_ros_service_request(
    const custom_type::Request & source,
    ros_message_type::Request & destination)
  {
    destination.load_namespace = source;
  }

  static void
  convert_to_custom_service_request(
    const ros_message_type::Request & source,
    custom_type::Request & destination)
  {
    destination = source.load_namespace;
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



