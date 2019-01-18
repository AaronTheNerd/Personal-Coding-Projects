// Written by Aaron Barge
// Copyright 2019

#ifndef _BINARY_SEARCH_TREE_CC_
#define _BINARY_SEARCH_TREE_CC_
#include "binarySearchTree.h"
#endif
Tree::Tree() {
  this->root = nullptr;
}
void Tree::Add(int val) {
  Node n(val);
  if (this->root == nullptr)
    root = &n;
  else
    Insert(root, val);
}
int Tree::Pop() {
  int ret_val = root->val_;
  Remove(ret_val);
  return ret_val;
}
void Tree::Remove(int val) {
  root = Remove(root, val);
}
bool Tree::Contains(int val) {
  return Contains(root, val);
}
int Tree::Top() {
  return root->val_;
}
Tree::Node::Node(int val) {
  this->left_child_ = nullptr;
  this->right_child_ = nullptr;
  this->val_ = val;
}
Tree::Node *Tree::Insert(Node *current, int val) {
  if (current == nullptr) {
    Node n(val);
    current = &n;
  } else if (val < current->val_) {
    current->left_child_ = Insert(current->left_child_, val);
  } else if (val >= current->val_) {
    current->right_child_ = Insert(current->right_child_, val);
  }
  return current;
}
bool Tree::Contains(Node *current, int val) {
  if (current == nullptr)
    return false;
  if (current->val_ == val)
    return true;
  else if (val < current->val_)
    return Contains(current->left_child_, val);
  else
    return Contains(current->right_child_, val);
}
Tree::Node *Tree::Remove(Node *current, int val) {
  if (current == nullptr)
    return nullptr;
  if (val < current->val_)
    current->left_child_ = Remove(current->left_child_, val);
  else if (val > current->val_)
    current->right_child_ = Remove(current->right_child_, val);
  else {
    Node *temp = current;
    current = FindMinFrom(current->right_child_);
    current->right_child_ = RemoveMinFrom(temp->right_child_);
    current->left_child_ = temp->left_child_;
  }
  return current;
}
Tree::Node *Tree::FindMinFrom(Node *current) {
  if (current == nullptr)
    return nullptr;
  if (current->left_child_ == nullptr)
    return current->left_child_;
  else
    return FindMinFrom(current->left_child_);
}
Tree::Node *Tree::RemoveMinFrom(Node *current) {
  if (current == nullptr)
    return nullptr;
  if (current->left_child_ == nullptr)
    return current->right_child_;
  current->left_child_ = RemoveMinFrom(current->left_child_);
  return current;
}