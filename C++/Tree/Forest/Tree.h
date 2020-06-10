// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_TREE_H_
#define _FOREST_TREE_H_


template <class T>
class Tree {
 public:
  virtual void Add(T) = 0;
  virtual void Remove(T) = 0;
  virtual bool Contains(T) const = 0;
  virtual T Top() const = 0;
  virtual T Pop() = 0;
  virtual unsigned int Size() const = 0;
  virtual unsigned int MaxDepth() const = 0;
  virtual unsigned int Depth(T) const = 0;
  virtual void Print() const = 0;
  virtual void PrintTop() const = 0;
 protected:
  template <typename N>
  class Edge {
   public:
    N* to;
    Edge() { to = NULL; }
    Edge(N* to_) { to = to_; }
    ~Edge() { delete(to); }
    N* operator->() { return to; }
    N& operator*() { return *to; }
  };
  class Node {
   public:
    T val;
  };
  Node* root;
};
#endif