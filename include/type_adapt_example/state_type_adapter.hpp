#include <string>

#include "rclcpp/type_adapter.hpp"
#include "lifecycle_msgs/msg/state.hpp"

struct CustomState
{
  static constexpr unsigned char PRIMARY_STATE_UNKNOWN = 0;
  static constexpr unsigned char PRIMARY_STATE_UNCONFIGURED = 1;
  static constexpr unsigned char PRIMARY_STATE_INACTIVE = 2;
  static constexpr unsigned char PRIMARY_STATE_ACTIVE = 3;
  static constexpr unsigned char PRIMARY_STATE_FINALIZED = 4;
  static constexpr unsigned char TRANSITION_STATE_CONFIGURING = 10;
  static constexpr unsigned char TRANSITION_STATE_CLEANINGUP = 11;
  static constexpr unsigned char TRANSITION_STATE_SHUTTINGDOWN = 12;
  static constexpr unsigned char TRANSITION_STATE_ACTIVATING = 13;
  static constexpr unsigned char TRANSITION_STATE_DEACTIVATING = 14;
  static constexpr unsigned char TRANSITION_STATE_ERRORPROCESSING = 15;

  unsigned char id;
  std::string label;
};

template<>
struct rclcpp::TypeAdapter<CustomState, lifecycle_msgs::msg::State>
{
  using is_specialized = std::true_type;
  using custom_type = CustomState;
  using ros_message_type = lifecycle_msgs::msg::State;

  static void
  convert_to_ros_message(
    const custom_type & source,
    ros_message_type & destination)
  {
    destination.id = source.id;
    destination.label = source.label;
  }

  static void
  convert_to_custom(
    const ros_message_type & source,
    custom_type & destination)
  {
    destination.id = source.id;
    destination.label = source.label;
  }
};
