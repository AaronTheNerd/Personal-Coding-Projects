// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_DOUBLY_LINKED_TREE_CC_
#define _FOREST_DOUBLY_LINKED_TREE_CC_
#include <iostream>
#include "DoublyLinkedTree.h"
#endif


/*
 * Constructors
 */
template <class T>
DLTree<T>::DLTree() {
  this->root = NULL;
}
template <class T>
DLTree<T>::DLNode::DLNode() {
  this->val = NULL;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
DLTree<T>::DLNode::DLNode(T val) {
  this->val = val;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
DLTree<T>::DLNode::DLNode(T val, DLEdge left, DLEdge right, DLEdge parent) {
  this->val = val;
  this->left = left;
  this->right = right;
  this->parent = parent;
}


/*
 * Destuctor
 */
template <class T>
DLTree<T>::~DLTree() {
  DestroyTree(this->root);
}
template <class T>
void DLTree<T>::DestroyTree(DLTree<T>::DLNode* current) {
  if (current != NULL) {
    DestroyTree(current->left.to);
    DestroyTree(current->right.to);
    delete current;
  }
}
template <class T>
DLTree<T>::DLNode::~DLNode() {
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}


/*
 * Node addition
 */
template <class T>
void DLTree<T>::Add(T val) {
  if (this->root == NULL)
    this->root = new DLNode(val);
  Insert(this->root, NULL, val);
}
template <class T>
typename DLTree<T>::DLNode* DLTree<T>::Insert(DLTree<T>::DLNode* current, DLTree<T>::DLNode* previous, T val) {
  if (current == NULL) {
    current = new DLNode(val);
    current->parent.to = previous;
  } else if (val < current->val) {
    current->left.to = Insert(current->left.to, current, val);
  } else if (val > current->val) {
    current->right.to = Insert(current->right.to, current, val);
  }
  return current;
}


/*
 * Node removal
 */
template <class T>
void DLTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}
template <class T>
typename DLTree<T>::DLNode* DLTree<T>::Remove(DLTree<T>::DLNode* current, T val) {
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
    DLTree<T>::DLNode* temp = FindMinFrom(current->right.to);
    current->val = temp->val;
    current->right.to = Remove(current->right.to, temp->val);
  }
  return current;
}
template <class T>
typename DLTree<T>::DLNode* DLTree<T>::FindMinFrom(DLTree<T>::DLNode* current) const {
  if (current == NULL)
    return NULL;
  if (current->left.to == NULL)
    return current;
  return FindMinFrom(current->left.to);
}
template <class T>
typename DLTree<T>::DLNode* DLTree<T>::RemoveMinFrom(DLTree<T>::DLNode* current) {
  if (current == NULL)
    return NULL;
  if (current->left.to == NULL)
    return current->right.to;
  current->left.to = RemoveMinFrom(current->left.to);
  return current;
}


/*
 * Search method
 */
template <class T>
bool DLTree<T>::Contains(T val) const {
  return Contains(this->root, val);
}
template <class T>
bool DLTree<T>::Contains(DLTree<T>::DLNode* current, T val) const {
  if (current == NULL) {
    return false;
  } else if (current->val == val) {
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
T DLTree<T>::Top() const {
  if (this->root)
    return this->root->val;
  else
    return NULL;
    
}


/*
 * Pop off top method
 */
template <class T>
T DLTree<T>::Pop() {
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
unsigned int DLTree<T>::Size() const {
  return Size(this->root);
}
template <class T>
unsigned int DLTree<T>::Size(DLTree<T>::DLNode* current) const {
  if (current == NULL)
    return 0;
  else
    return 1 + Size(current->left.to) + Size(current->right.to);
  
}
template <class T>
unsigned int DLTree<T>::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
template <class T>
unsigned int DLTree<T>::MaxDepth(DLTree<T>::DLNode* current, unsigned int curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    unsigned int left_depth = MaxDepth(current->left.to, curr_depth + 1);
    unsigned int right_depth = MaxDepth(current->right.to, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
template <class T>
unsigned int DLTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val);
}
template <class T>
unsigned int DLTree<T>::Depth(DLTree<T>::DLNode* current, T val) const {
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
void DLTree<T>::Print() const {
  PrintInOrder(this->root);
  std::cout << std::endl << std::endl;
}
template <class T>
void DLTree<T>::PrintInOrder(DLTree<T>::DLNode* current) const {
  if (current == NULL)
    return;
  PrintInOrder(current->left.to);
  std::cout << current->val << std::endl;
  PrintInOrder(current->right.to);
}


/*
 * Print memory locations for top (debugging)
 */
template <class T>
void DLTree<T>::PrintTop() const {
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