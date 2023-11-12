#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

#include "trigger_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedTriggerStruct = rclcpp::TypeAdapter<CustomTrigger, std_srvs::srv::Trigger>;

class TriggerClientNode : public rclcpp::Node
{
public:
  TriggerClientNode() : Node("my_trigger_client_node")
  {
    client = this->create_client<AdaptedTriggerStruct>("custom_trigger");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomTrigger::Request>();
  }

  rclcpp::Client<AdaptedTriggerStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomTrigger::Request> request;
private:

};

class TriggerServerNode : public rclcpp::Node
{
public:
TriggerServerNode()
: Node("my_trigger_server_node")
{
  service = this->create_service<AdaptedTriggerStruct>("custom_trigger",
    std::bind(&TriggerServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedTriggerStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<CustomTrigger::Request> & req, std::shared_ptr<CustomTrigger::Response> res)
{
  res->success = true;
  res->message = "Message";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}

/*
void ros_call(const std::shared_ptr<std_srvs::srv::Trigger::Request> & req, std::shared_ptr<std_srvs::srv::Trigger::Response> res)
{
  res->success = true;
  res->message = "Message";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}
*/

};

