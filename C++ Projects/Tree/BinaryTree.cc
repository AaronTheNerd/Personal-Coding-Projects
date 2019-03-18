// Written by Aaron Bnarge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _TREE_BINARY_SEARCH_TREE_CC_
#define _TREE_BINARY_SEARCH_TREE_CC_
#include "BinaryTree.h"
#endif
template <class T>
using BTSNode = BinaryTree<T>::Node;
template <class T>
BinaryTree<T>::BinaryTree() {
  this->root = NULL;
}
template <class T>
void BinaryTree<T>::Add(T val_) {
  if (this->root == NULL)
    this->root = new Node(val_);
  if (!this->Contains(val_))
    Insert(this->root, val_);
}
template <class T>
BTSNode* BinaryTree<T>::Insert(BinaryTree<T>::Node* current, T val) {
  if (current == NULL)
    current = new Node(val);
  else if (val < current->val)
    current->left = Insert(current->left, val);
  else if (val > current->val)
    current->right = Insert(current->right, val);
  return current;
}
template <class T>
void BinaryTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}
template <class T>
BinaryTree<T>::Node* BinaryTree<T>::Remove(BinaryTree<T>::Node* current, T val) {
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
    BinaryTree<T>::Node* temp = new Node(current->val, current->left, current->right_child_);
    current = FindMinFrom(current->right);
    current->right = RemoveMinFrom(temp->right);
    current->left = temp->left;
    delete temp;
  }
  return current;
}
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
template <class T>
T BinaryTree<T>::Top() const {
  if (this->root)
    return this->root->val;
  else
    return NULL;
}
template <class T>
void BinaryTree<T>::Print() const {
  this->PrintInOrder(this->root);
}
template <class T>
void BinaryTree<T>::PrintInOrder(BinaryTree<T>::Node* curr) const {
  if (curr == NULL)
    return;
  PrintInOrder(curr->left);
  std::cout << curr->val << std::endl;
  PrintInOrder(curr->right);
}