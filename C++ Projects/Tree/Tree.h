// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_H_
#define _TREE_H_


template <class T>
class Tree {
 public:
  virtual void Add(T) = 0;
  virtual void Remove(T) = 0;
  virtual bool Contains(T) const = 0;
  virtual T Top() const = 0;
  virtual T Pop() = 0;
  virtual size_t Size() const = 0;
  virtual size_t MaxDepth() const = 0;
  virtual size_t Depth(T) const = 0;
  virtual void Print() const = 0;
  virtual void PrintTop() const = 0;
 private:
  class Node {
   public:
    Node();
    Node(T);
    T val;
  };
  Node* root;
};
#endif