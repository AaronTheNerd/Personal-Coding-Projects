// Written by Aaron Barge
// Copyright 2019

#ifndef _BINARY_SEARCH_TREE_CC_
#define _BINARY_SEARCH_TREE_CC_
#include "binarySearchTree.h"
#include <iostream>
#endif
Tree::Tree() {
  this->root = NULL;
}
void Tree::Add(int val) {
  if (this->root == NULL)
    this->root = new Node(val);
  if (!this->Contains(val))
    Insert(this->root, val);
}
int Tree::Pop() {
  int ret_val = root->val_;
  Remove(ret_val);
  return ret_val;
}
void Tree::Remove(int val) {
  this->root = Remove(this->root, val);
}
bool Tree::Contains(int val) {
  return Contains(this->root, val);
}
int Tree::Top() {
  return this->root->val_;
}
Tree::Node::Node() {
  this->val_ = 0;
  this->left_child_ = NULL;
  this->right_child_ = NULL;
}
Tree::Node::Node(int val) {
  this->left_child_ = NULL;
  this->right_child_ = NULL;
  this->val_ = val;
}
Tree::Node::Node(int val, Tree::Node* left, Tree::Node* right) {
  this->left_child_ = left;
  this->right_child_ = right;
  this->val_ = val;
}
Tree::Node *Tree::Insert(Tree::Node *current, int val) {
  if (current == NULL) {
    current = new Node(val);
  } else if (val < current->val_) {
    current->left_child_ = Insert(current->left_child_, val);
  } else if (val > current->val_) {
    current->right_child_ = Insert(current->right_child_, val);
  }
  return current;
}
bool Tree::Contains(Tree::Node *current, int val) {
  if (current == NULL)
    return false;
  if (current->val_ == val) {
    return true;
  } else if (val < current->val_) {
    if (current->left_child_) 
      return Contains(current->left_child_, val);
    else
      return false;
  } else {
    if (current->right_child_)
      return Contains(current->right_child_, val);
    else
      return false;
  }
}
Tree::Node *Tree::Remove(Tree::Node *current, int val) {
  if (current == NULL)
    return NULL;
  if (val < current->val_)
    current->left_child_ = Remove(current->left_child_, val);
  else if (val > current->val_)
    current->right_child_ = Remove(current->right_child_, val);
  else {
    if (current->right_child_ == NULL)
      return current->left_child_;
    if (current->left_child_ == NULL) 
      return current->right_child_;
    Tree::Node *temp = new Node(current->val_, current->left_child_, current->right_child_);
    current = FindMinFrom(current->right_child_);
    current->right_child_ = RemoveMinFrom(temp->right_child_);
    current->left_child_ = temp->left_child_;
  }
  return current;
}
Tree::Node *Tree::FindMinFrom(Tree::Node *current) {
  if (current == NULL)
    return NULL;
  if (current->left_child_ == NULL)
    return current;
  else
    return FindMinFrom(current->left_child_);
}
Tree::Node *Tree::RemoveMinFrom(Tree::Node *current) {
  if (current == NULL)
    return NULL;
  if (current->left_child_ == NULL)
    return current->right_child_;
  current->left_child_ = RemoveMinFrom(current->left_child_);
  return current;
}
void Tree::PrintInOrder() {
  PrintInOrder(root);
  std::cout << std::endl;
}
void Tree::PrintInOrder(Tree::Node* current) {
  if (current == NULL)
    return;
  if (current->left_child_)
    PrintInOrder(current->left_child_);
  std::cout << current->val_ << std::endl;
  if (current->right_child_)
    PrintInOrder(current->right_child_);
}
void Tree::PrintTop() {
  std::cout << "The address of the root is: " << this->root << std::endl;
  if (this->root) {
    std::cout << "  The Root is not NULL" << std::endl;
    std::cout << "  And its value is: " << this->root->val_ << std::endl;
  } else {
    std::cout << "  The Root is NULL" << std::endl;
  }
  std::cout << "The address of the root's left child is: " << this->root->left_child_ << std::endl;
  if (this->root->left_child_) {
    std::cout << "  The left child is not NULL " << std::endl;
    std::cout << "  And its value is: " << this->root->left_child_->val_ << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right_child_ << std::endl;
  if (this->root->right_child_) {
    std::cout << "  The right child is not NULL " << std::endl;
    std::cout << "  And its value is: " << this->root->right_child_->val_ << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}