#include <memory>

#include "rclcpp/type_adapter.hpp"
#include "lifecycle_msgs/srv/get_state.hpp"
#include "lifecycle_msgs/msg/state.hpp"

#include "state_type_adapter.hpp"

struct CustomGetState
{
  CustomState current_state;
  struct Empty {};

  using Request = Empty;
  using Response = CustomState;
};

using StateTypeAdapter = rclcpp::TypeAdapter<CustomState, lifecycle_msgs::msg::State>;

template<>
struct rclcpp::TypeAdapter<CustomGetState, lifecycle_msgs::srv::GetState>
{
  using is_specialized = std::true_type;
  using custom_type = CustomGetState;
  using ros_message_type = lifecycle_msgs::srv::GetState;

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
    StateTypeAdapter::convert_to_ros_message(source, destination.current_state);
  }

  static void
  convert_to_custom_service_response(
    const ros_message_type::Response & source,
    custom_type::Response & destination)
  {
    StateTypeAdapter::convert_to_custom(source.current_state, destination);
  }
};
