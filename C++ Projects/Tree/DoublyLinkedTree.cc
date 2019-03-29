// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_DOUBLY_LINKED_TREE_CC_
#define _TREE_DOUBLY_LINKED_TREE_CC_
#include <iostream>
#include "DoublyLinkedTree.h"
#endif


/*
 * Constructors
 */
template <class T>
DLTree<T>::DLTree() {
  this->root == NULL;
}
template <class T>
DLTree<T>::Node::Node() {
  this->val = NULL;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
DLTree<T>::Node::Node(T val) {
  this->val = val;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
DLTree<T>::Node::Node(T val, DLTree<T>::Node* left, DLTree<T>::Node* right, DLTree<T>::Node* parent) {
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
void DLTree<T>::DestroyTree(DLTree<T>::Node* current) {
  if (current != NULL) {
    DestroyTree(current->left);
    DestroyTree(current->right);
    delete current;
  }
}
template <class T>
DLTree<T>::Node::~Node() {
  delete left, right, parent;
}


/*
 * Node addition
 */
template <class T>
void DLTree<T>::Add(T val) {
  if (this->root == NULL)
    this->root = new Node(val);
  Insert(this->root, NULL, val);
}
template <class T>
typename DLTree<T>::Node* DLTree<T>::Insert(DLTree<T>::Node* current, DLTree<T>::Node* previous, T val) {
  if (current == NULL) {
    current = new Node(val);
    current->parent = previous;
  } else if (val < current->val) {
    current->left = Insert(current->left, current, val);
  } else if (val > current->val) {
    current->right = Insert(current->right, current, val);
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
typename DLTree<T>::Node* DLTree<T>::Remove(DLTree<T>::Node* current, T val) {
  if (current == NULL)
    return NULL;
  if (val < current->val)
    current->left = Remove(current->left, val);
  else if (val > current->val)
    current->right = Remove(current->right, val);
  else {
    if (current->right == NULL) {
      if (current->left != NULL)
        current->left->parent = current->parent;
      return current->left;
    }
    if (current->left == NULL) {
      current->right->parent = current->parent;
      return current->right;
    }
    DLTree<T>::Node* temp = new Node(current->val, current->left, current->right, current->parent);
    current = FindMinFrom(current->right);
    current->right = RemoveMinFrom(temp->right);
    current->left = temp->left;
    return current;
  }
}
template <class T>
typename DLTree<T>::Node* DLTree<T>::FindMinFrom(DLTree<T>::Node* current) const {
  if (current == NULL)
    return NULL;
  if (current->left == NULL)
    return current;
  return FindMinFrom(current->left);
}
template <class T>
typename DLTree<T>::Node* DLTree<T>::RemoveMinFrom(DLTree<T>::Node* current) {
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
bool DLTree<T>::Contains(T val) const {
  return BinaryTree<T>::Contains(this->root, val);
}


/*
 * Top method
 */
template <class T>
T DLTree<T>::Top() const {
  return BinaryTree<T>::Top();
}


/*
 * Pop off top method
 */
template <class T>
T DLTree<T>::Pop() {
  if (this->root != NULL)
    return BinaryTree<T>::Pop();
  return NULL;
}


/*
 * Size and Depth methods
 */
template <class T>
size_t DLTree<T>::Size() const {
  return BinaryTree<T>::Size();
}
template <class T>
size_t DLTree<T>::MaxDepth() const {
  return BinaryTree<T>::MaxDepth();
}
template <class T>
size_t DLTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val);
}
template <class T>
size_t DLTree<T>::Depth(DLTree<T>::Node* current, T val) const {
  if (this == NULL)
    return -1;
  if (current->val < val)
    return Depth(current->right, val);
  if (current->val > val)
    return Depth(current->left, val);
  size_t depth = 0;
  while (current != this->root) {
    depth++;
    current = current->parent;
  }
  return depth;
}


/*
 * Print method 
 */
template <class T>
void DLTree<T>::Print() const {
  BinaryTree<T>::Print();
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
  std::cout << "The address of the root's left child is: " << this->root->left << std::endl;
  if (this->root->left) {
    std::cout << "  And its value is: " << this->root->left->val << std::endl;
    std::cout << "  It is connected to the root" << (this->root->left->parent == this->root ? "TRUE":"FALSE") << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right << std::endl;
  if (this->root->right) {
    std::cout << "  It is connected to the root" << (this->root->right->parent == this->root ? "TRUE" : "FALSE") << std::endl;
    std::cout << "  And its value is: " << this->root->right->val << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}