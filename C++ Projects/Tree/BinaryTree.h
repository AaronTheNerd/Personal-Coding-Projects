// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_BINARY_SEARCH_TREE_H_
#define _TREE_BINARY_SEARCH_TREE_H_
#include "Tree.h"
template <class T>
class BinaryTree : public Tree<T> {
 public:
  BinaryTree<T>();
  void Add(T val);
  void Remove(T val);
  bool Contains(T val) const;
  T Top() const;
  void Print();
  void PrintInOrder() const;
  void PrintPostOrder() const;
 private:
  class Node<T> {
    Node<T>();
    Node<T>(T val);
    Node<T>(T val, Node<T>* left_, Node<T>* right_);
    Node<T>* left;
    Node<T>* right;
    T val;
  };
  Node<T>* root;
};
#endif