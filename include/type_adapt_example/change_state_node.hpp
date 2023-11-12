#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "lifecycle_msgs/srv/change_state.hpp"

#include "change_state_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedChangeStateStruct = rclcpp::TypeAdapter<CustomChangeState, lifecycle_msgs::srv::ChangeState>;

class ChangeStateClientNode : public rclcpp::Node
{
public:
  ChangeStateClientNode() : Node("my_change_state_client_node")
  {
    client = this->create_client<AdaptedChangeStateStruct>("custom_change_state");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomChangeState::Request>();
  }

  rclcpp::Client<AdaptedChangeStateStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomChangeState::Request> request;
private:

};

class ChangeStateServerNode : public rclcpp::Node
{
public:
ChangeStateServerNode()
: Node("my_change_state_server_node")
{
  service = this->create_service<AdaptedChangeStateStruct>("custom_change_state",
    std::bind(&ChangeStateServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedChangeStateStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<CustomChangeState::Request> & req, std::shared_ptr<CustomChangeState::Response> res)
{
  res = std::make_shared<bool>(true);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}

/*
void ros_call(const std::shared_ptr<lifecycle_msgs::srv::ChangeState::Request> & req, std::shared_ptr<lifecycle_msgs::srv::ChangeState::Response> res)
{
  res->success = true;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}
*/

};

