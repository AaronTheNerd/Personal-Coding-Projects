// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_TWO_THREE_TREE_CC_
#define _FOREST_TWO_THREE_TREE_CC_
#include <iostream>
#include "TwoThreeTree.h"
#endif


/*
 * Constructors
 */
template <class T>
TTTree<T>::TTTree() {
  this->root = NULL;
}
template <class T>
TTTree<T>::TwoNode::TwoNode(T val) {
  this->t1 = val;
  this->left = NULL;
  this->right = NULL;
}
template <class T>
TTTree<T>::ThreeNode::ThreeNode() {
  this->t1 = NULL;
  this->t2 = NULL;
  this->left = NULL;
  this->right = NULL;
  this->middle = NULL;
}
template <class T>
TTTree<T>::ThreeNode::ThreeNode(TTTree<T>::TwoNode n, T val) {
  if (val < n.t1) {
    this->t1 = val;
    this->t2 = n.t1;
  } else {
    this->t1 = n.t1;
    this->t2 = val;
  }
  this->left = NULL;
  this->right = NULL;
  this->middle = NULL;
}


/*
 * Destuctor
 */
template <class T>
TTTree<T>::~TTTree() {
  DestroyTree(this->root);
}
template <class T>
void TTTree<T>::DestroyTree(TTTree<T>::TTNode* current) {
  if (current != NULL) {
    DestroyTree(current->left.to);
    DestroyTree(current->right.to);
    DestroyTree(current->middle.to);
    delete current;
  }
}
template <class T>
TTTree<T>::TwoNode::~TwoNode() {
  this->left = this->right = NULL;
}
template <class T>
TTTree<T>::ThreeNode::~ThreeNode() {
  this->left = this->right = NULL;
}

/*
 * Node addition
 */
template <class T>
void TTTree<T>::Add(T val) {
  if (this->root == NULL)
    this->root = new TTNode(val);
  Insert(this->root, NULL, val);
}
template <class T>
typename TTTree<T>::TTNode* TTTree<T>::Insert(TTTree<T>::TTNode* current, TTTree<T>::TTNode* previous, T val) {
  if (current == NULL) {
    return NULL;
  } else if (current->left.to == NULL
      && current->right.to == NULL
      && current->middle.to == NULL) {
    
  }
  /*
  if (current == NULL) {
    current = new TTNode(val);
    current->parent.to = previous;
  } else if (val < current->val) {
    current->left.to = Insert(current->left.to, current, val);
  } else if (val > current->val) {
    current->right.to = Insert(current->right.to, current, val);
  }
  return current;
  */
}


/*
 * Node removal
 */
template <class T>
void TTTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}


/*
 * Search method
 */
template <class T>
bool TTTree<T>::Contains(T val) const {
  return false;
}


/*
 * Top method
 */
template <class T>
T TTTree<T>::Top() const {
  return 0;
}


/*
 * Pop off top method
 */
template <class T>
T TTTree<T>::Pop() {
  return 0;
}


/*
 * Size and Depth methods
 */
template <class T>
unsigned int TTTree<T>::Size() const {
  return Size(this->root);
}
template <class T>
unsigned int TTTree<T>::Size(TTTree<T>::TTNode* current) const {
  if (current == NULL)
    return 0;
  else
    return 1 + Size(current->left.to) + Size(current->right.to);
  
}
template <class T>
unsigned int TTTree<T>::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
template <class T>
unsigned int TTTree<T>::MaxDepth(TTTree<T>::TTNode* current, unsigned int curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    unsigned int left_depth = MaxDepth(current->left.to, curr_depth + 1);
    unsigned int right_depth = MaxDepth(current->right.to, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
template <class T>
unsigned int TTTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val);
}
template <class T>
unsigned int TTTree<T>::Depth(TTTree<T>::TTNode* current, T val) const {
  if (this->root == NULL)
    return 0;
  if (current->val < val)
    return Depth(current->right.to, val);
  if (current->val > val)
    return Depth(current->left.to, val);
  size_t depth = 0;
  while (current != this->root) {
    depth++;
    current = current->parent.to;
  }
 return depth;
}


/*
 * Print method 
 */
template <class T>
void TTTree<T>::Print() const {
  PrintInOrder(this->root);
  std::cout << std::endl << std::endl;
}


/*
 * Print memory locations for top (debugging)
 */
template <class T>
void TTTree<T>::PrintTop() const {
  std::cout << "The address of the root is: " << this->root << std::endl;
  if (this->root)
    std::cout << "  And its value is: " << this->root->val << std::endl;
  else
    std::cout << "  And its value is NULL" << std::endl;
  std::cout << "The address of the root's left child is: " << this->root->left.to << std::endl;
  if (this->root->left.to) {
    std::cout << "  And its value is: " << this->root->left->val << std::endl;
    std::cout << "  It is connected to the root " << (this->root->left->parent.to == this->root ? "TRUE":"FALSE") << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right.to << std::endl;
  if (this->root->right.to) {
    std::cout << "  It is connected to the root " << (this->root->right->parent.to == this->root ? "TRUE" : "FALSE") << std::endl;
    std::cout << "  And its value is: " << this->root->right->val << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}