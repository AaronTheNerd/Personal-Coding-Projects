// Written by Aaron Barge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _TREE_BINARY_SEARCH_TREE_H_
#define _TREE_BINARY_SEARCH_TREE_H_
#include "Tree.h"


template <class T>
class BinaryTree : public Tree<T> {
 public:
  BinaryTree();
  void Add(T);
  void Remove(T);
  bool Contains(T) const;
  T Top() const;
  T Pop();
  void Print() const;
  void PrintTop() const;
  class Node {
   public:
    Node();
    Node(T val);
    Node(T val, Node* left_, Node* right_);
    Node* left;
    Node* right;
    T val;
  };
 private:
  Node* root;
  Node* Insert(Node*, T);
  Node* Remove(Node*, T);
  bool Contains(Node*, T) const;
  void PrintInOrder(Node*) const;
  Node* FindMinFrom(Node* current);
  Node* RemoveMinFrom(Node* current);
};
#include "../Tree/BinaryTree.cc"
#endif