#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "type_adapt_example/set_bool_node.hpp"
#include "type_adapt_example/add_diagnostics_node.hpp"
#include "type_adapt_example/empty_node.hpp"
#include "type_adapt_example/trigger_node.hpp"
#include "type_adapt_example/change_state_node.hpp"
#include "type_adapt_example/get_state_node.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  // Make a bunch of different clients
  for(int i = 0; i < 20; i++)
  {
    std::shared_ptr<SetBoolClientNode> set_bool_client = std::make_shared<SetBoolClientNode>();
    std::shared_ptr<AddDiagnosticsClientNode> add_diagnostics_client = std::make_shared<AddDiagnosticsClientNode>();
    std::shared_ptr<EmptyClientNode> empty_client = std::make_shared<EmptyClientNode>();
    std::shared_ptr<TriggerClientNode> trigger_client = std::make_shared<TriggerClientNode>();
    std::shared_ptr<ChangeStateClientNode> change_state_client = std::make_shared<ChangeStateClientNode>();
    std::shared_ptr<GetStateClientNode> get_state_client = std::make_shared<GetStateClientNode>();
  };

  std::shared_ptr<SetBoolClientNode> set_bool_client = std::make_shared<SetBoolClientNode>();
  std::shared_ptr<AddDiagnosticsClientNode> add_diagnostics_client = std::make_shared<AddDiagnosticsClientNode>();
  std::shared_ptr<EmptyClientNode> empty_client = std::make_shared<EmptyClientNode>();
  std::shared_ptr<TriggerClientNode> trigger_client = std::make_shared<TriggerClientNode>();
  std::shared_ptr<ChangeStateClientNode> change_state_client = std::make_shared<ChangeStateClientNode>();
  std::shared_ptr<GetStateClientNode> get_state_client = std::make_shared<GetStateClientNode>();

  auto set_bool_result = set_bool_client->client->async_send_request(set_bool_client->request);
  auto add_diagnostics_result = add_diagnostics_client->client->async_send_request(add_diagnostics_client->request);
  auto empty_result = empty_client->client->async_send_request(empty_client->request);
  auto trigger_result = trigger_client->client->async_send_request(trigger_client->request);
  auto change_state_result = change_state_client->client->async_send_request(change_state_client->request);
  auto get_state_result = get_state_client->client->async_send_request(get_state_client->request);

  rclcpp::spin_until_future_complete(set_bool_client, set_bool_result);
  rclcpp::spin_until_future_complete(add_diagnostics_client, add_diagnostics_result);
  rclcpp::spin_until_future_complete(empty_client,empty_result);
  rclcpp::spin_until_future_complete(trigger_client, trigger_result);
  rclcpp::spin_until_future_complete(change_state_client, change_state_result);
  rclcpp::spin_until_future_complete(get_state_client, get_state_result);
  rclcpp::shutdown();
}
