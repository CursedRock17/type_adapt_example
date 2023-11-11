#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "type_adapt_example/set_bool_node.hpp"
#include "type_adapt_example/add_diagnostics_node.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<SetBoolServerNode> set_bool_server = std::make_shared<SetBoolServerNode>();
  std::shared_ptr<AddDiagnosticsServerNode> add_diagnostics_server = std::make_shared<AddDiagnosticsServerNode>();

  rclcpp::spin(set_bool_server);
  rclcpp::spin(add_diagnostics_server);

  rclcpp::shutdown();
}
