#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "type_adapt_example/set_bool_node.hpp"
#include "type_adapt_example/add_diagnostics_node.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<SetBoolClientNode> set_bool_client = std::make_shared<SetBoolClientNode>();
  std::shared_ptr<AddDiagnosticsClientNode> add_diagnostics_client = std::make_shared<AddDiagnosticsClientNode>();

  auto set_bool_result = set_bool_client->client->async_send_request(set_bool_client->request);
  auto add_diagnostics_result = add_diagnostics_client->client->async_send_request(add_diagnostics_client->request);

  rclcpp::spin_until_future_complete(set_bool_client, set_bool_result);
  rclcpp::spin_until_future_complete(add_diagnostics_client, add_diagnostics_result);
  rclcpp::shutdown();
}
