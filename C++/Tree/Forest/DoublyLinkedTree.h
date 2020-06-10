// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_DOUBLY_LINKED_TREE_H_
#define _TREE_DOUBLY_LINKED_TREE_H_
#include "BinaryTree.h"


template <class T>
class DLTree : public BinaryTree<T> {
 public:
  DLTree();                      // Default tree constructor
  ~DLTree();                     // Tree desturctor
  void Add(T);                   // Adds a value to the tree
  void Remove(T);                // Removes a value from the tree
  bool Contains(T) const;        // Searches tree for a value
  T Top() const;                 // Returns the root's value
  T Pop();                       // Pops the root off and returns value
  unsigned int Size() const;     // Returns the number of elements in the tree
  unsigned int MaxDepth() const; // Returns the maximum depth of the tree
  unsigned int Depth(T) const;   // Returns the depth of the node with the specified value
                                 // It is good to note that this is fairly inefficient compared to
                                 // binary tree's implementation. Where the binary tree's implementation
                                 // Keeps track of the current depth while searching this one does not
                                 // and instead just uses the parent edge to go to the root
  void Print() const;            // Print's the tree's values using an in-order traversal
  void PrintTop() const;         // Method to print the top of the tree's references
 protected:
  class DLNode : public BinaryTree<T>::BSTNode {
   public:
    typedef typename Tree<T>::template Edge<DLNode> DLEdge;
    DLNode();                      // Default node constructor
    DLNode(T);                     // Node constructor with only value
    DLNode(T, DLEdge, DLEdge, DLEdge);   // Explicit Node constructor
    ~DLNode();                     // Node destructor
    DLEdge parent, left, right;
  };                             // Helper methods and root
  DLNode* root;
  void DestroyTree(DLNode*);
  DLNode* Insert(DLNode*, DLNode*, T);
  DLNode* Remove(DLNode*, T);
  bool Contains(DLNode*, T) const;
  unsigned int Depth(DLNode*, T) const;
  DLNode* FindMinFrom(DLNode*) const;
  DLNode* RemoveMinFrom(DLNode*);
  unsigned int Size(DLNode*) const;
  unsigned int MaxDepth(DLNode*, unsigned int) const;
  void PrintInOrder(DLNode*) const;
};
#include "DoublyLinkedTree.cc"
#endif