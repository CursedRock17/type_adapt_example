#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"

#include "empty_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedEmptyStruct = rclcpp::TypeAdapter<CustomEmpty, std_srvs::srv::Empty>;

class EmptyClientNode : public rclcpp::Node
{
public:
  EmptyClientNode() : Node("my_empty_client_node")
  {
    client = this->create_client<AdaptedEmptyStruct>("custom_empty");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomEmpty::Request>();
  }

  rclcpp::Client<AdaptedEmptyStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomEmpty::Request> request;
private:

};

class EmptyServerNode : public rclcpp::Node
{
public:
EmptyServerNode()
: Node("my_empty_server_node")
{
  service = this->create_service<AdaptedEmptyStruct>("custom_empty",
    std::bind(&EmptyServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedEmptyStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<CustomEmpty::Request> & req, std::shared_ptr<CustomEmpty::Response> res)
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}

/*
void ros_call(const std::shared_ptr<std_srvs::srv::Empty::Request> & req, std::shared_ptr<std_srvs::srv::Empty::Response> res)
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback");
}
*/

};

