// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_TWO_THREE_TREE_H_
#define _FOREST_TWO_THREE_TREE_H_
#include "Tree.h"

template <class T>
class TTTree : public Tree<T> {
 public:
  TTTree();
  ~TTTree();
  void Add(T);
  void Remove(T);
  bool Contains(T) const;
  T Top() const;
  T Pop();
  unsigned int Size() const;
  unsigned int MaxDepth() const;
  unsigned int Depth(T) const;
  void Print() const;
  void PrintTop() const;
 protected:
  class TTNode : public Tree<T>::Node {
   public:
    typedef typename Tree<T>::template Edge<TTNode> TTEdge;
  };
  class TwoNode : public TTNode {
    T t1;
    TTEdge left, right;
    TwoNode(T);
    ~TwoNode();
  };
  class ThreeNode : public TTNode {
    T t1, t2;
    TTEdge left, right, middle;
    ThreeNode();
    ThreeNode(TwoNode, T);
    ~ThreeNode();
  };
  Node* root;
 private:
  void DestroyTree(TTNode*);
  TTNode* Insert(TTNode*, TTNode*, T);
  unsigned int Size(TTNode*) const;
  unsigned int MaxDepth(TTNode*, unsigned int) const;
  unsigned int Depth(TTNode*, T) const;
};
#include "TwoThreeTree.cc"
#endif