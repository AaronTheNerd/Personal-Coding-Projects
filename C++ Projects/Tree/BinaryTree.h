// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_BINARY_SEARCH_TREE_H_
#define _TREE_BINARY_SEARCH_TREE_H_
#include "Tree.h"
template <class T>
class BinaryTree : public Tree<T> {
 public:
  BinaryTree<T>();
  void Add(T);
  void Remove(T);
  bool Contains(T) const;
  T Top() const;
  void Print() const;
  void PrintInOrder() const;
  void PrintPostOrder() const;
  class Node<T> {
   public:
    Node<T>();
    Node<T>(T val);
    Node<T>(T val, Node<T>* left_, Node<T>* right_);
   private:
    Node<T>* left;
    Node<T>* right;
    T val;
  };
 private:
  Node<T>* root;
  Node* Insert(Node<T>*, T);
  Node* Remove(Node<T>*, T);
  bool Contains(Node<T>*, T) const;
};
#include "BinaryTree.cc"
#endif