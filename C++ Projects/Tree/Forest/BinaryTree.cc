// Written by Aaron Bnarge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _FOREST_BINARY_TREE_CC_
#define _FOREST_BINARY_TREE_CC_
#include <iostream>
#include "Tree.h"
#include "BinaryTree.h"
#endif


/*
 * Constructors
 */
template <class T>
BinaryTree<T>::BinaryTree() {
  this->root = NULL;
}
template <class T>
BinaryTree<T>::BSTNode::BSTNode() {
  this->val = 0;
  this->left = NULL;
  this->right = NULL;
}
template <class T>
BinaryTree<T>::BSTNode::BSTNode(T val) {
  this->left = NULL;
  this->right = NULL;
  this->val = val;
}
template <class T>
BinaryTree<T>::BSTNode::BSTNode(T val, BSTEdge left, BSTEdge right) {
  this->left = left;
  this->right = right;
  this->val = val;
}


/*
 * Destructor
 */
template <class T>
BinaryTree<T>::~BinaryTree() {
  DestroyTree(this->root);
}
template <class T>
void BinaryTree<T>::DestroyTree(BinaryTree<T>::BSTNode* current) {
  if (current != NULL) {
    DestroyTree(current->left.to);
    DestroyTree(current->right.to);
    delete current;
  }
}
template <class T>
BinaryTree<T>::BSTNode::~BSTNode() {
  this->left = NULL;
  this->right = NULL;
}


/*
 * Node addition
 */
template <class T>
void BinaryTree<T>::Add(T val_) {
  if (this->root == NULL)
    this->root = new BSTNode(val_);
  Insert(this->root, val_);
}
template <class T>
typename BinaryTree<T>::BSTNode* BinaryTree<T>::Insert(BinaryTree<T>::BSTNode* current, T val) {
  if (current == NULL)
    current = new BSTNode(val);
  else if (val < current->val)
    current->left.to = Insert(current->left.to, val);
  else if (val > current->val)
    current->right.to = Insert(current->right.to, val);
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
typename BinaryTree<T>::BSTNode* BinaryTree<T>::Remove(BinaryTree<T>::BSTNode* current, T val) {
  if (current == NULL)
    return NULL;
  if (val < current->val)
    current->left.to = Remove(current->left.to, val);
  else if (val > current->val)
    current->right.to = Remove(current->right.to, val);
  else {
    if (current->right.to == NULL) {
      return current->left.to;
    }
    if (current->left.to == NULL) {
      return current->right.to;
    }
    BinaryTree<T>::BSTNode* temp = FindMinFrom(current->right.to);
    current->val = temp->val;
    current->right.to = Remove(current->right.to, temp->val);
  }
  return current;
}
template <class T>
typename BinaryTree<T>::BSTNode* BinaryTree<T>::FindMinFrom(BinaryTree<T>::BSTNode* current) const {
  if (current == NULL)
    return NULL;
  if (current->left.to == NULL)
    return current;
  else
    return FindMinFrom(current->left.to);
}


/*
 * Search method
 */
template <class T>
bool BinaryTree<T>::Contains(T val) const {
  return Contains(this->root, val);
}
template <class T>
bool BinaryTree<T>::Contains(BinaryTree<T>::BSTNode* current, T val) const {
  if (current == NULL)
    return false;
  if (current->val == val) {
    return true;
  } else if (val < current->val) {
    return Contains(current->left.to, val);
  } else {
    return Contains(current->right.to, val);
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
  if (this->root != NULL) {
    T ret_val = this->root->val;
    Remove(ret_val);
    return ret_val;
  }
  return NULL;
}


/*
 * Size and Depth methods
 */
template <class T>
unsigned int BinaryTree<T>::Size() const {
  return Size(this->root);
}
template <class T>
unsigned int BinaryTree<T>::Size(BinaryTree<T>::BSTNode* current) const {
  if (current == NULL)
    return 0;
  else
    return 1 + Size(current->left.to) + Size(current->right.to);
}
template <class T>
unsigned int BinaryTree<T>::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
template <class T>
unsigned int BinaryTree<T>::MaxDepth(BinaryTree<T>::BSTNode* current, unsigned int curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    unsigned int left_depth = MaxDepth(current->left.to, curr_depth + 1);
    unsigned int right_depth = MaxDepth(current->right.to, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
template <class T>
unsigned int BinaryTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val, 0);
}
template <class T>
unsigned int BinaryTree<T>::Depth(BinaryTree<T>::BSTNode* current, T val, unsigned int curr_depth) const {
  if (current == NULL)
    return -1;
  if (current->val == val)
    return curr_depth;
  if (current->val > val)
    return Depth(current->left.to, val, curr_depth + 1);
  else
    return Depth(current->right.to, val, curr_depth + 1);
}


/*
 * Print method 
 */
template <class T>
void BinaryTree<T>::Print() const {
  PrintInOrder(this->root);
  std::cout << std::endl;
}
template <class T>
void BinaryTree<T>::PrintInOrder(BinaryTree<T>::BSTNode* curr) const {
  if (curr == NULL)
    return;
  PrintInOrder(curr->left.to);
  std::cout << curr->val << std::endl;
  PrintInOrder(curr->right.to);
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
  std::cout << "The address of the root's left child is: " << this->root->left.to << std::endl;
  if (this->root->left.to) {
    std::cout << "  And its value is: " << this->root->left->val << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right.to << std::endl;
  if (this->root->right.to) {
    std::cout << "  And its value is: " << this->root->right->val << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}