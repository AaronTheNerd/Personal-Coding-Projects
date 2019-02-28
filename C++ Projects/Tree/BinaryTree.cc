// Written by Aaron Bnarge
// Copyright 2019

#ifndef _TREE_BINARY_SEARCH_TREE_CC_
#define _TREE_BINARY_SEARCH_TREE_CC_
#include "BinaryTree.h"
#endif

template <class T>
BinaryTree<T>::BinaryTree<T>() {
  this->root = NULL;
}
template <class T>
void BinaryTree<T>::Add(T val_) {
  if (this->root == NULL)
    this->root = new Node(val);
  if (!this->Contains(val))
    Insert(this->root, val)
}
template <class T>
BinaryTree<T>::Node* BinaryTree<T>::Insert(BinaryTree<T>::Node<T>* current, T val) {
  if (current == NULL)
    current = new Node(val);
  else if (val < current->val_)
    current->left_child_ = Insert(current->left_child_, val);
  else if (val > current->val_)
    current->right_child_ = Insert(current->right_child_, val);
  return current;
}
template <class T>
void BinaryTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}
template <class T>
BinaryTree<T>::Node* BinaryTree<T>::Remove(BinaryTree<T>::Node<T>* current, T val) {
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
    BinaryTree<T>::Node* temp = new Node(current->val_, current->left_child_, current->right_child_);
    current = FindMinFrom(current->right_child_);
    current->right_child_ = RemoveMinFrom(temp->right_child_);
    current->left_child_ = temp->left_child_;
    delete temp;
  }
  return current;
}
template <class T>
bool BinaryTree<T>::Contains(T val) const {
  return Contains(this->root, val);
}
template <class T>
bool BinaryTree<T>::Contains(BinaryTree<T>::Node<T>* current, T val) const {
  if (current == NULL)
    return false;
  if (current->val_ == val) {
    return true;
  } else if (val < current->val_) {
    return Contains(current->left_child_, val);
  } else {
    return Contains(current->right_child_, val);
  }
}
template <class T>
T BinaryTree<T>::Top() const {
  return this->root->val_;
}
