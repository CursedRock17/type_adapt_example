#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

#include "set_bool_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedSetBoolStruct = rclcpp::TypeAdapter<CustomBool, std_srvs::srv::SetBool>;

class SetBoolClientNode : public rclcpp::Node
{
public:
  SetBoolClientNode() : Node("my_set_bool_client_node")
  {
    client = this->create_client<AdaptedSetBoolStruct>("custom_set_bool");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomBool::Request>();
  }

  rclcpp::Client<AdaptedSetBoolStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomBool::Request> request;
private:

};

class SetBoolServerNode : public rclcpp::Node
{
public:
SetBoolServerNode()
: Node("my_set_bool_server_node")
{
  service = this->create_service<AdaptedSetBoolStruct>("custom_set_bool",
    std::bind(&SetBoolServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedSetBoolStruct>::SharedPtr service = nullptr;

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

