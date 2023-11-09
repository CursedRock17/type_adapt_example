
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

#include "type_adapt_example/set_bool_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

using AdaptedTypeStruct = rclcpp::TypeAdapter<CustomBool, std_srvs::srv::SetBool>;

class ServerNode : public rclcpp::Node
{
public:
ServerNode()
: Node("my_server_node")
{
  service = this->create_service<AdaptedTypeStruct>("custom_service",
    std::bind(&ServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedTypeStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<bool> & req, std::shared_ptr<CustomBool::Response> res)
{
  res->success = req.get();
  res->message = "There is Data";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback: %s", res->message.c_str());
}

void ros_call(const std::shared_ptr<std_srvs::srv::SetBool::Request> & req, std::shared_ptr<std_srvs::srv::SetBool::Response> res)
{
  res->success = req.get();
  res->message = "There is Data";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback: %s", res->message.c_str());
}

};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ServerNode>();

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send custom data.");

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
