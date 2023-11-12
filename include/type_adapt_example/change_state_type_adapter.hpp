#include <string>
#include <memory>

#include "rclcpp/type_adapter.hpp"
#include "lifecycle_msgs/srv/change_state.hpp"
#include "lifecycle_msgs/msg/transition.hpp"

#include "transition_type_adapter.hpp"

struct CustomChangeState
{
  CustomTransition transition;
  bool success;

  using Request = CustomTransition;
  using Response = bool;
};

using TransitionTypeAdapter = rclcpp::TypeAdapter<CustomTransition, lifecycle_msgs::msg::Transition>;

template<>
struct rclcpp::TypeAdapter<CustomChangeState, lifecycle_msgs::srv::ChangeState>
{
  using is_specialized = std::true_type;
  using custom_type = CustomChangeState;
  using ros_message_type = lifecycle_msgs::srv::ChangeState;

  static void
  convert_to_ros_service_request(
    const custom_type::Request & source,
    ros_message_type::Request & destination)
  {
    TransitionTypeAdapter::convert_to_ros_message(source, destination.transition);
  }

  static void
  convert_to_custom_service_request(
    const ros_message_type::Request & source,
    custom_type::Request & destination)
  {
    TransitionTypeAdapter::convert_to_custom(source.transition, destination);
  }

  static void
  convert_to_ros_service_response(
    const custom_type::Response & source,
    ros_message_type::Response & destination)
  {
    destination.success = source;
  }

  static void
  convert_to_custom_service_response(
    const ros_message_type::Response & source,
    custom_type::Response & destination)
  {
    destination = source.success;
  }
};
