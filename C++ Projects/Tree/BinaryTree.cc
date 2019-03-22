// Written by Aaron Bnarge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _TREE_BINARY_SEARCH_TREE_CC_
#define _TREE_BINARY_SEARCH_TREE_CC_
#include "BinaryTree.h"
#include <iostream>
#endif


/*
 * Constructors
 */
template <class T>
BinaryTree<T>::BinaryTree() {
  this->root = NULL;
}
template <class T>
BinaryTree<T>::Node::Node() {
  this->val = 0;
  this->left = NULL;
  this->right = NULL;
}
template <class T>
BinaryTree<T>::Node::Node(T val) {
  this->left = NULL;
  this->right = NULL;
  this->val = val;
}
template <class T>
BinaryTree<T>::Node::Node(T val, BinaryTree<T>::Node* left, BinaryTree<T>::Node* right) {
  this->left = left;
  this->right = right;
  this->val = val;
}


/*
 * Node addition
 */
template <class T>
void BinaryTree<T>::Add(T val_) {
  if (this->root == NULL)
    this->root = new Node(val_);
  if (!this->Contains(val_))
    Insert(this->root, val_);
}
template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(BinaryTree<T>::Node* current, T val) {
  if (current == NULL)
    current = new Node(val);
  else if (val < current->val)
    current->left = Insert(current->left, val);
  else if (val > current->val)
    current->right = Insert(current->right, val);
  return current;
}


/*
 * Node removal
 */
template <class T>
void BinaryTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}
template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::Remove(BinaryTree<T>::Node* current, T val) {
  if (current == NULL)
    return NULL;
  if (val < current->val)
    current->left = Remove(current->left, val);
  else if (val > current->val)
    current->right = Remove(current->right, val);
  else {
    if (current->right == NULL)
      return current->left;
    if (current->left == NULL)
      return current->right;
    BinaryTree<T>::Node* temp = new Node(current->val, current->left, current->right);
    current = FindMinFrom(current->right);
    current->right = RemoveMinFrom(temp->right);
    current->left = temp->left;
    delete temp;
  }
  return current;
}
template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::FindMinFrom(BinaryTree<T>::Node* current) {
  if (current == NULL)
    return NULL;
  if (current->left == NULL)
    return current;
  else
    return FindMinFrom(current->left);
}
template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::RemoveMinFrom(BinaryTree<T>::Node* current) {
  if (current == NULL)
    return NULL;
  if (current->left == NULL)
    return current->right;
  current->left = RemoveMinFrom(current->left);
  return current;
}


/*
 * Search method
 */
template <class T>
bool BinaryTree<T>::Contains(T val) const {
  return Contains(this->root, val);
}
template <class T>
bool BinaryTree<T>::Contains(BinaryTree<T>::Node* current, T val) const {
  if (current == NULL)
    return false;
  if (current->val == val) {
    return true;
  } else if (val < current->val) {
    return Contains(current->left, val);
  } else {
    return Contains(current->right, val);
  }
}


/*
 * Top method
 */
template <class T>
T BinaryTree<T>::Top() const {
  if (this->root)
    return this->root->val;
  else
    return NULL;
}


/*
 * Pop off top method
 */
template <class T>
T BinaryTree<T>::Pop() {
  int ret_val = root->val;
  Remove(ret_val);
  return ret_val;
}


/*
 * Size and Depth methods
 */
template <class T>
size_t BinaryTree<T>::Size() const {
  return Size(this->root);
}
template <class T>
size_t BinaryTree<T>::Size(BinaryTree<T>::Node* current) const {
  if (current == NULL)
    return 0;
  else
    return 1 + Size(current->left) + Size(current->right);
}
template <class T>
size_t BinaryTree<T>::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
template <class T>
size_t BinaryTree<T>::MaxDepth(BinaryTree<T>::Node* current, size_t curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    size_t left_depth = MaxDepth(current->left, curr_depth + 1);
    size_t right_depth = MaxDepth(current->right, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
template <class T>
size_t BinaryTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val, 0);
}
template <class T>
size_t BinaryTree<T>::Depth(BinaryTree<T>::Node* current, T val, size_t curr_depth) const {
  if (current == NULL)
    return -1;
  if (current->val == val)
    return curr_depth;
  if (current->val > val)
    return Depth(current->left, val, curr_depth + 1);
  else
    return Depth(current->right, val, curr_depth + 1);
}


/*
 * Print method 
 */
template <class T>
void BinaryTree<T>::Print() const {
  this->PrintInOrder(this->root);
  std::cout << std::endl;
}
template <class T>
void BinaryTree<T>::PrintInOrder(BinaryTree<T>::Node* curr) const {
  if (curr == NULL)
    return;
  PrintInOrder(curr->left);
  std::cout << curr->val << std::endl;
  PrintInOrder(curr->right);
}


/*
 * Print memory locations for top (debugging)
 */
template <class T>
void BinaryTree<T>::PrintTop() const {
  std::cout << "The address of the root is: " << this->root << std::endl;
  if (this->root) {
    std::cout << "  And its value is: " << this->root->val << std::endl;
  } else {
    std::cout << "  The Root is NULL" << std::endl;
  }
  std::cout << "The address of the root's left child is: " << this->root->left << std::endl;
  if (this->root->left) {
    std::cout << "  And its value is: " << this->root->left->val << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right << std::endl;
  if (this->root->right) {
    std::cout << "  And its value is: " << this->root->right->val << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}