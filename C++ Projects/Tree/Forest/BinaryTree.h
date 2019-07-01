// Written by Aaron Barge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _TREE_BINARY_SEARCH_TREE_H_
#define _TREE_BINARY_SEARCH_TREE_H_
#include <cstddef>
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
  class Node {
   public:
    class Edge {
     public:
      Node* to;
      Edge() { to = NULL; }
      Edge(Node* to_) { to = to_; }
      ~Edge() { delete(to); }
      Node* operator->() { return to; }
      Node& operator*() { return *to; }
    };
    Node();                      // Default node constructor
    Node(T);                     // Node constructor with only value
    Node(T, Edge, Edge);         // Explicit Node constructor
    ~Node();                     // Node destructor
    Edge left;
    Edge right;
    T val;
  };                             // Helper methods and root
  Node* root;
  void DestroyTree(Node*);
  Node* Insert(Node*, T);
  Node* Remove(Node*,  T);
  Node* FindMinFrom(Node*) const;
  bool Contains(Node*, T) const;
  void PrintInOrder(Node*) const;
  unsigned int Size(Node*) const;
  unsigned int MaxDepth(Node*, unsigned int) const;
  unsigned int Depth(Node*, T, unsigned int) const;
};

#include "BinaryTree.cc"
#endif