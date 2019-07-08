// Written by Aaron Barge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _FOREST_BINARY_SEARCH_TREE_H_
#define _FOREST_BINARY_SEARCH_TREE_H_
#include "Tree.h"


template <typename T>
class BinaryTree : public Tree<T> {
 public:
  BinaryTree();                  // Default tree constructor
  ~BinaryTree();                 // Tree destructor
  void Add(T);                   // Adds a value to the tree
  void Remove(T);                // Removes a value from the tree
  bool Contains(T) const;        // Searches tree for a value
  T Top() const;                 // Returns the root's value
  T Pop();                       // Pops the root off and returns value
  unsigned int Size() const;     // Returns the number of elements in the tree
  unsigned int MaxDepth() const; // Returns the maximum depth of the tree
  unsigned int Depth(T) const;   // Returns the depth of the node with the specified value
  void Print() const;            // Print's the tree's values using an in-order traversal
  void PrintTop() const;         // Method to print the top of the tree's references
 protected:
  class BSTNode : public Tree<T>::Node {
   public:
    typedef typename Tree<T>::template Edge<BSTNode> BSTEdge;
    BSTNode();                      // Default node constructor
    BSTNode(T);                     // Node constructor with only value
    BSTNode(T, BSTEdge, BSTEdge);         // Explicit Node constructor
    ~BSTNode();                     // Node destructor
    BSTEdge left;
    BSTEdge right;
    T val;
  };                             // Helper methods and root
  BSTNode* root;
  void DestroyTree(BSTNode*);
  BSTNode* Insert(BSTNode*, T);
  BSTNode* Remove(BSTNode*,  T);
  BSTNode* FindMinFrom(BSTNode*) const;
  bool Contains(BSTNode*, T) const;
  void PrintInOrder(BSTNode*) const;
  unsigned int Size(BSTNode*) const;
  unsigned int MaxDepth(BSTNode*, unsigned int) const;
  unsigned int Depth(BSTNode*, T, unsigned int) const;
};

#include "BinaryTree.cc"
#endif