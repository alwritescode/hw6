#include "tree.cc"

auto test_tree() {
  auto j = create_tree(9, 90);
  auto i = create_tree(8, 80);
  auto h = create_tree(7, 70, i, j);
  auto g = create_tree(6, 60, h);
  auto f = create_tree(5, 50, nullptr, g);
  auto e = create_tree(4, 40);
  auto d = create_tree(3, 30);
  auto c = create_tree(2, 20, nullptr, e);
  auto b = create_tree(1, 10, c, d);
  auto a = create_tree(0, 00, b, f);
  return a;
}
/* looks like:
      0
   /    \
  1      5
 / \      \
2   3      6
 \        /
  4      7
        / \
       8   9
*/

int main() {
  auto tree = test_tree();
  std::string searchpath = "RRL";
  key_type searchkey = 3;

  auto foundnode = node_at(tree, searchpath);
  if (foundnode) {        // to prevent searching for key or value on nullptr
    std::cout << "Node at path " << searchpath << " has key " << foundnode->key_ << " and value " << foundnode->value_ << std::endl;
  }
  else {
    std::cout << "No node at this path." << std::endl;
  }

  std::string foundpath = path_to(tree, searchkey);
  if (foundpath != "-") {
    std::cout << "Found " << searchkey << " at " << foundpath << std::endl;
  }
  else {
    std::cout << "Could not find node with this key." << std::endl;
  }

  destroy_tree(tree);
  return 0;
}
