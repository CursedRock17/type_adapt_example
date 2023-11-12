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

  // Make a bunch of different services
  for (int i = 0; i < 20; i++)
  {
    std::shared_ptr<SetBoolServerNode> set_bool_server = std::make_shared<SetBoolServerNode>();
    std::shared_ptr<AddDiagnosticsServerNode> add_diagnostics_server = std::make_shared<AddDiagnosticsServerNode>();
    std::shared_ptr<EmptyServerNode> empty_server = std::make_shared<EmptyServerNode>();
    std::shared_ptr<TriggerServerNode> trigger_server = std::make_shared<TriggerServerNode>();
    std::shared_ptr<ChangeStateServerNode> change_state_server = std::make_shared<ChangeStateServerNode>();
    std::shared_ptr<GetStateServerNode> get_state_server = std::make_shared<GetStateServerNode>();
  }

  std::shared_ptr<SetBoolServerNode> set_bool_server = std::make_shared<SetBoolServerNode>();
  std::shared_ptr<AddDiagnosticsServerNode> add_diagnostics_server = std::make_shared<AddDiagnosticsServerNode>();
  std::shared_ptr<EmptyServerNode> empty_server = std::make_shared<EmptyServerNode>();
  std::shared_ptr<TriggerServerNode> trigger_server = std::make_shared<TriggerServerNode>();
  std::shared_ptr<ChangeStateServerNode> change_state_server = std::make_shared<ChangeStateServerNode>();
  std::shared_ptr<GetStateServerNode> get_state_server = std::make_shared<GetStateServerNode>();

  rclcpp::spin(set_bool_server);
  rclcpp::spin(add_diagnostics_server);
  rclcpp::spin(empty_server);
  rclcpp::spin(trigger_server);
  rclcpp::spin(change_state_server);
  rclcpp::spin(get_state_server);

  rclcpp::shutdown();
}
