#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "type_adapt_example/typed_string_node.hpp"
#include "type_adapt_example/string_type_adapter.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<TypedStringNodeSub> string_node = std::make_shared<TypedStringNodeSub>();
  rclcpp::spin(string_node);
  rclcpp::shutdown();
}
