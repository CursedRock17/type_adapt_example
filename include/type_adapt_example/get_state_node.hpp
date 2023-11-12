#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "lifecycle_msgs/srv/get_state.hpp"

#include "get_state_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedGetStateStruct = rclcpp::TypeAdapter<CustomGetState, lifecycle_msgs::srv::GetState>;

class GetStateClientNode : public rclcpp::Node
{
public:
  GetStateClientNode() : Node("my_get_state_client_node")
  {
    client = this->create_client<AdaptedGetStateStruct>("custom_get_state");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomGetState::Request>();
  }

  rclcpp::Client<AdaptedGetStateStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomGetState::Request> request;
private:

};

class GetStateServerNode : public rclcpp::Node
{
public:
GetStateServerNode()
: Node("my_get_state_server_node")
{
  service = this->create_service<AdaptedGetStateStruct>("custom_get_state",
    std::bind(&GetStateServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedGetStateStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<CustomGetState::Request> & req, std::shared_ptr<CustomGetState::Response> res)
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}

/*
void ros_call(const std::shared_ptr<lifecycle_msgs::srv::GetState::Request> & req, std::shared_ptr<lifecycle_msgs::srv::GetState::Response> res)
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}
*/

};

