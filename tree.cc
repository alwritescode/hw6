#include <iostream>
#include <cassert>
#include <vector>
#include "tree.hh"

tree_ptr_t create_tree(const key_type& key,        // return a new tree object that has been created
                       const value_type& value,
                       tree_ptr_t left,
                       tree_ptr_t right) {
  tree_ptr_t ntree = new Tree;
  (*ntree).key_ = key;
  (*ntree).value_ = value;
  (*ntree).left_ = left;
  (*ntree).right_ = right;
  return ntree;
}

void destroy_tree(tree_ptr_t tree) {      // deallocate all space used by the tree and all branches
  if (tree->left_) {
    destroy_tree(tree->left_);
  }
  if (tree->right_) {
    destroy_tree(tree->right_);
  }
  delete tree;      // deallocates memory at tree_ptr_t (pointer) for each tree, deleting each branch at a time
}

std::vector<std::string> path_helper(tree_ptr_t leaf, key_type key) {    // recursive helper function for path_to
  if (leaf->key_ == key) {      // base case for recursion: return empty string on which to add L/R steps of path
    return {""};
  }

  else {
    std::vector<std::string> npaths = {};

    if (leaf->left_) {        // check it isn't nullptr to avoid those pesky segmentation errors
      std::vector<std::string> lpaths = path_helper(leaf->left_, key);  // recusively get a vector of level n paths to the left

      for (std::string path : lpaths) {
        std::string npath = "L" + path;     // expand each path to level n+1
        npaths.push_back(npath);
      }
    }

    if (leaf->right_) {
      std::vector<std::string> rpaths = path_helper(leaf->right_, key);  // get vector of right branch paths

      for (std::string path : rpaths) {
        std::string npath = "R" + path;
        npaths.push_back(npath);
      }
    }

    return npaths;
    }

    if (leaf->left_ == nullptr && leaf->right_ == nullptr) {  // indicating dead-end path
      return {"-"};
    }
  }

std::string path_to(tree_ptr_t tree, key_type key) {
  // this probably (definitely) isn't a very efficient way of doing this, but it was the only way I could figure out
  // to discard dead-end recursion paths

  std::vector<std::string> allpaths = path_helper(tree, key);

  for (std::string path : allpaths) {
    if (path.find('-') == std::string::npos) {    // true if the path doesn't have "-", indicating it returned without hitting a dead-end (so must have hit the right value)
      return path;
    }
  }
  return "-";     // if nothing is returned in the loop, it can be assumed that all paths were dead ends, thus the key is not in the tree
}

tree_ptr_t node_at(tree_ptr_t tree, std::string path) {   // return node found at the end of a given path
  char instruct;
  for (int i = 0; i < path.length(); i++) {    // loops through for the number of instruction characters in path
    instruct = path.at(i);
    if (instruct == 'L') {   // * to look at the character at address instruct
      tree = tree->left_;
    }
    else {
      if (instruct == 'R') {
        tree = tree->right_;
      }
      else {
        return nullptr;    // invalid character or no branches
      }
    }
  }
  return tree;
}
