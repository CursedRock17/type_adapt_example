#include <string>
#include <memory>
#include <functional>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "string_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

using StringTypeAdapter = rclcpp::TypeAdapter<std::string, std_msgs::msg::String>;

class TypedStringNodeSub : public rclcpp::Node
{
public:
  TypedStringNodeSub() : Node("string_subscription_node")
  {
    this->create_subscription<StringTypeAdapter>("custom_string",
      10, std::bind(&TypedStringNodeSub::callback, this, _1));
  }

private:
    void callback(const std::string & msg)
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.c_str());
    };
    rclcpp::Subscription<StringTypeAdapter>::SharedPtr subscription = nullptr;
};

class TypedStringNodePub : public rclcpp::Node
{
public:
  TypedStringNodePub() : Node("string_publisher_node")
  {
    timer = this->create_wall_timer(500ms, std::bind(&TypedStringNodePub::callback, this));
    publisher = this->create_publisher<StringTypeAdapter>("custom_string", 10);
  }


private:
  rclcpp::Publisher<StringTypeAdapter>::SharedPtr publisher = nullptr;
  rclcpp::TimerBase::SharedPtr timer;

  void callback()
  {
    std::string str = "King";
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Hello: %s", str.c_str());
    publisher->publish(std::move(str));
  }

};
