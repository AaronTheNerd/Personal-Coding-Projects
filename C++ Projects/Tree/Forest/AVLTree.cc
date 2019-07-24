// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_AVL_TREE_CC_
#define _FOREST_AVL_TREE_CC_
#include <iostream>
#include <string>
#include "AVLTree.h"
#endif


/*
 * Constructors
 */
template <class T>
AVLTree<T>::AVLTree() {
  this->root = NULL;
}
template <class T>
AVLTree<T>::AVLNode::AVLNode() {
  this->val = 0;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
AVLTree<T>::AVLNode::AVLNode(T val) {
  this->val = val;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
}
template <class T>
AVLTree<T>::AVLNode::AVLNode(T val, AVLEdge left, AVLEdge right, AVLEdge parent) {
  this->val = val;
  this->left = left;
  this->right = right;
  this->parent = parent;
}


/*
 * Destuctor
 */
template <class T>
AVLTree<T>::~AVLTree() {
  DestroyTree(this->root);
}
template <class T>
void AVLTree<T>::DestroyTree(AVLTree<T>::AVLNode* current) {
  if (current != NULL) {
    DestroyTree(current->left.to);
    DestroyTree(current->right.to);
    delete current;
  }
}
template <class T>
AVLTree<T>::AVLNode::~AVLNode() {
  this->left = this->right = this->parent = NULL;
}


/*
 * Node addition
 */
template <class T>
void AVLTree<T>::Add(T val) {
  if (this->root == NULL)
    this->root = new AVLNode(val);
  std::string path = std::string("");
  this->Insert(this->root, NULL, val, path);
  bool unbalanced = this->CheckWeights();
  if (unbalanced) {
    AVLTree<T>::AVLNode* new_node = this->GetNode(path);
    AVLTree<T>::AVLNode* unbalanced_node = this->GetUnbalanced(new_node);
    std::string last_moves = path.substr(path.size() - 2, 2);
    if (last_moves == "11") {
      this->Left(unbalanced_node);
    } else if (last_moves == "00") {
      this->Right(unbalanced_node);
    } else if (last_moves == "10") {
      this->Left(unbalanced_node);
      this->Right(unbalanced_node->parent.to);
    } else {
      this->Right(unbalanced_node);
      this->Left(unbalanced_node->parent.to);
    }
  }
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::Insert(AVLTree<T>::AVLNode* current, AVLTree<T>::AVLNode* previous, T val, std::string& path) {
  if (current == NULL) {
    current = new AVLNode(val);
    current->parent.to = previous;
  } else if (val < current->val) {
    path += std::string("0");
    current->left.to = this->Insert(current->left.to, current, val, path);
  } else if (val > current->val) {
    path += std::string("1");
    current->right.to = this->Insert(current->right.to, current, val, path);
  }
  return current;
}
template <class T>
bool AVLTree<T>::CheckWeights() {
  return this->CheckWeights(this->root);
}
template <class T>
bool AVLTree<T>::CheckWeights(AVLTree<T>::AVLNode* current) {
  if (current == NULL) {
    return false;
  } else if (current->left.to == NULL && current->right.to == NULL) {
    current->weight = 0;
  } else {
    current->weight = this->Size(current->left.to) - this->Size(current->left.to);
    if (current->weight > 1 || current->weight < -1) {
      this->CheckWeights(current->left.to);
      this->CheckWeights(current->right.to);
      return true;
    } else {
      return this->CheckWeights(current->left.to) || this->CheckWeights(current->right.to);
    }
  }
  return false;
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::GetNode(std::string path) const {
  AVLTree<T>::AVLNode* current = this->root;
  for (unsigned int i = 0; i < path.size(); ++i) {
    if (path[i] == '0') {
      current = current->left.to;
    } else {
      current = current->right.to;
    }
  }
  return current;
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::GetUnbalanced(AVLTree<T>::AVLNode* curr) const {
  int curr_weight = curr->weight;
  while (curr_weight <= 1 && curr_weight >= -1) {
    curr = curr->parent.to;
    curr_weight = curr->weight;
  }
  return curr;
}
template <class T>
void AVLTree<T>::Left(AVLTree<T>::AVLNode* a) {
  return;
};
template <class T>
void AVLTree<T>::Right(AVLTree<T>::AVLNode* a) {
  return;
}


/*
 * Node removal
 */
template <class T>
void AVLTree<T>::Remove(T val) {
  this->root = Remove(this->root, val);
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::Remove(AVLTree<T>::AVLNode* current, T val) {
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
    AVLTree<T>::AVLNode* temp = FindMinFrom(current->right.to);
    current->val = temp->val;
    current->right.to = Remove(current->right.to, temp->val);
  }
  return current;
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::FindMinFrom(AVLTree<T>::AVLNode* current) const {
  if (current == NULL)
    return NULL;
  if (current->left.to == NULL)
    return current;
  return FindMinFrom(current->left.to);
}
template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::RemoveMinFrom(AVLTree<T>::AVLNode* current) {
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
bool AVLTree<T>::Contains(T val) const {
  return Contains(this->root, val);
}
template <class T>
bool AVLTree<T>::Contains(AVLTree<T>::AVLNode* current, T val) const {
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
T AVLTree<T>::Top() const {
  return (this->root == NULL) ? NULL : this->root->val;
}


/*
 * Pop off top method
 */
template <class T>
T AVLTree<T>::Pop() {
  if (this->root != NULL) {
    T ret_val = this->Top();
    Remove(this->root, ret_val);
    return ret_val;
  }
  return NULL;
}


/*
 * Size and Depth methods
 */
template <class T>
unsigned int AVLTree<T>::Size() const {
  return Size(this->root);
}
template <class T>
unsigned int AVLTree<T>::Size(AVLTree<T>::AVLNode* current) const {
  if (current == NULL)
    return 0;
  else
    return 1 + Size(current->left.to) + Size(current->right.to);
  
}
template <class T>
unsigned int AVLTree<T>::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
template <class T>
unsigned int AVLTree<T>::MaxDepth(AVLTree<T>::AVLNode* current, unsigned int curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    unsigned int left_depth = MaxDepth(current->left.to, curr_depth + 1);
    unsigned int right_depth = MaxDepth(current->right.to, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
template <class T>
unsigned int AVLTree<T>::Depth(T val) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, val);
}
template <class T>
unsigned int AVLTree<T>::Depth(AVLTree<T>::AVLNode* current, T val) const {
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
void AVLTree<T>::Print() const {
  PrintInOrder(this->root);
  std::cout << std::endl << std::endl;
}
template <class T>
void AVLTree<T>::PrintInOrder(AVLTree<T>::AVLNode* current) const {
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
void AVLTree<T>::PrintTop() const {
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