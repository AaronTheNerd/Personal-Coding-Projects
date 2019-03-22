// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_DOUBLY_LINKED_TREE_H_
#define _TREE_DOUBLY_LINKED_TREE_H_
#include "BinaryTree.h"


template <class T>
class DLTree : public BinaryTree<T> {
 public:
  DLTree();
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
    Node* left;
    Node* right;
    Node* parent;
    T val;
  };
 private:
  Node* root;
};
#include "../Tree/DoublyLinkedTree.cc"
#endif