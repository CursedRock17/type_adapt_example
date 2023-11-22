#include <memory>
#include <functional>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class StringNodeSub : public rclcpp::Node
{
public:
  StringNodeSub() : Node("string_subscription_node")
  {
    this->create_subscription<std_msgs::msg::String>("custom_string",
      10, std::bind(&StringNodeSub::callback, this, _1));
  }

private:
    void callback(const std_msgs::msg::String & msg)
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    };
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription = nullptr;
};

class StringNodePub : public rclcpp::Node
{
public:
  StringNodePub() : Node("string_publisher_node")
  {
    timer = this->create_wall_timer(500ms, std::bind(&StringNodePub::callback, this));
    publisher = this->create_publisher<std_msgs::msg::String>("custom_string", 10);
  }


private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher = nullptr;
  rclcpp::TimerBase::SharedPtr timer;

  void callback()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "King";
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Hello: %s", msg.data.c_str());
    publisher->publish(msg);
  }

};
