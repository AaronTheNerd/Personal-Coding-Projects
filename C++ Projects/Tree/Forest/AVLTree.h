// Written by Aaron Barge
// Copyright 2019

#ifndef _FOREST_AVL_TREE_H_
#define _FOREST_AVL_TREE_H_
#include "DoublyLinkedTree.h"


template <typename T>
class AVLTree : public DLTree<T> {
 public:
  AVLTree();
  ~AVLTree();
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
  class AVLNode : public DLTree<T>::DLNode {
   public:
    typedef typename Tree<T>::template Edge<AVLNode> AVLEdge;
    AVLNode();                      // Default node constructor
    AVLNode(T);                     // Node constructor with only value
    AVLNode(T, AVLEdge, AVLEdge, AVLEdge);   // Explicit Node constructor
    ~AVLNode();                     // Node destructor
    AVLEdge left, right, parent;
    int weight;
  };                             // Helper methods and root
  AVLNode* root;
 private:
  void DestroyTree(AVLNode*);
  bool CheckWeights();
  bool CheckWeights(AVLNode*);
  AVLNode* GetNode(std::string) const;
  AVLNode* GetUnbalanced(AVLNode*) const;
  void Left(AVLNode*);
  void Right(AVLNode*);
  AVLNode* Insert(AVLNode*, AVLNode*, T, std::string&);
  AVLNode* Remove(AVLNode*, T);
  AVLNode* FindMinFrom(AVLNode*) const;
  AVLNode* RemoveMinFrom(AVLNode*);
  bool Contains(AVLNode*, T) const;
  unsigned int Size(AVLNode*) const;
  unsigned int MaxDepth(AVLNode*, unsigned int) const;
  unsigned int Depth(AVLNode*, T) const;
  void PrintInOrder(AVLNode*) const;
};

#include "AVLTree.cc"
#endif