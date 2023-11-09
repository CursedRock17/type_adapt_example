#include <future>
#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

#include "type_adapt_example/set_bool_type_adapter.hpp"

using namespace std::chrono_literals;
using AdaptedTypeStruct = rclcpp::TypeAdapter<CustomBool, std_srvs::srv::SetBool>;

class ClientNode : public rclcpp::Node
{
public:
  ClientNode() : Node("ClientNode")
  {
    client = this->create_client<AdaptedTypeStruct>("custom_service");

    while (!client->wait_for_service(1s))
    {
      if(!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting");
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request = std::make_shared<bool>();
  }

  rclcpp::Client<AdaptedTypeStruct>::SharedPtr client = nullptr;
  std::shared_ptr<bool> request;
private:

};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ClientNode>();
    auto result = node->client->async_send_request(node->request);

    if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %s", result.get()->message.c_str());
    } else {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call custom service");
    }

    rclcpp::shutdown();
    return 0;
}

