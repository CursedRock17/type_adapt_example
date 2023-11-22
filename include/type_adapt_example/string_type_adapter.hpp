#ifndef TYPEADAPTEXAMPLE__STRINGTYPEADAPTER__HPP_
#define TYPEADAPTEXAMPLE__STRINGTYPEADAPTER__HPP_

#include "rclcpp/type_adapter.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>

template<>
struct rclcpp::TypeAdapter<
   std::string,
   std_msgs::msg::String
>
{
  using is_specialized = std::true_type;
  using custom_type = std::string;
  using ros_message_type = std_msgs::msg::String;

  static
  void
  convert_to_ros_message(
    const custom_type & source,
    ros_message_type & destination)
  {
    destination.data = source;
  }

  static
  void
  convert_to_custom(
    const ros_message_type & source,
    custom_type & destination)
  {
    destination = source.data;
  }
};

#endif  // TYPEADAPTEXAMPLE__STRINGTYPEADAPTER__HPP_


