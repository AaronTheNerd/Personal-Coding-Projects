// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_H_
#define _TREE_H_
template <class T>
class Tree {
 public:
  virtual void Add(T val) = 0;
  virtual void Remove(T val) = 0;
  virtual bool Contains(T val) = 0;
  virtual T Top() = 0;
  virtual void Print() = 0;
 private:
  virtual class Node<T> {
   public:
    Node<T>();
    Node<T>(T val);
    T val;
  };
  Node<T>* root;
};
#endif