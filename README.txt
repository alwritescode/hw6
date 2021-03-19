The tree.cc file defines functions for a Tree data structure, as declared in tree.hh.

create_tree() simply creates a new Tree object and assigns values to this new Tree's members.

destroy_tree() recursively destroys the input Tree by deallocating each leaf.

path_to() uses a combination of recursion and iteration to determine the path to a given key value in the Tree.
  path_helper() is a recursive helper function for path_to(), which produces a vector of all paths in the Tree that end in either a dead-end (leaf with no left/right members), or the key value searched for.
  path_to() then iterates through the vector to check if each path is a dead-end, returning the first non-dead-end path, or if all are dead-end, returning "-".

node_at() uses simple recursion to follow a given path through a Tree, and returns the node found at the end of that path.

The test_tree.cc file includes tree.cc, defines a test Tree structure, and runs the functions defined in tree.cc on this test Tree, printing results.

test_tree() creates and combines leaves into a full Tree structure.

main() defines a key and path with which to use path_to() and node_at(), and prints out the resulting path to that key, and node key and value at that path.
