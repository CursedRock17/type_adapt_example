#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "diagnostic_msgs/srv/add_diagnostics.hpp"

#include "add_diagnostics_type_adapter.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using AdaptedAddDiagnosticsStruct = rclcpp::TypeAdapter<CustomAddDiagnostics, diagnostic_msgs::srv::AddDiagnostics>;

class AddDiagnosticsClientNode : public rclcpp::Node
{
public:
  AddDiagnosticsClientNode() : Node("my_add_diagnostics_client_node")
  {
    client = this->create_client<AdaptedAddDiagnosticsStruct>("custom_add_diagnostics");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<CustomAddDiagnostics::Request>();
  }

  rclcpp::Client<AdaptedAddDiagnosticsStruct>::SharedPtr client = nullptr;
  std::shared_ptr<CustomAddDiagnostics::Request> request;
private:

};

class AddDiagnosticsServerNode : public rclcpp::Node
{
public:
AddDiagnosticsServerNode() : Node("my_add_diagnostics_server_node")
{
  service = this->create_service<AdaptedAddDiagnosticsStruct>("custom_add_diagnostics",
    std::bind(&AddDiagnosticsServerNode::custom_call, this, _1, _2));
}

private:
rclcpp::Service<AdaptedAddDiagnosticsStruct>::SharedPtr service = nullptr;

void custom_call(const std::shared_ptr<CustomAddDiagnostics::Request> & req,
  std::shared_ptr<CustomAddDiagnostics::Response> res)
{
  res->success = true;
  res->message = "There is Data";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback: %s", res->message.c_str());
}

void ros_call(const std::shared_ptr<diagnostic_msgs::srv::AddDiagnostics::Request> & req, std::shared_ptr<diagnostic_msgs::srv::AddDiagnostics::Response> res)
{
  res->success = true;
  res->message = "There is Data";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Here's the Client Callback: %s", res->message.c_str());
}

};

