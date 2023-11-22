#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "type_adapt_example/string_node.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<StringNodePub> string_node = std::make_shared<StringNodePub>();
  rclcpp::spin(string_node);
  rclcpp::shutdown();
}
