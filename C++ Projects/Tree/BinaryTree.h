// Written by Aaron Barge
// Copyright 2019
// I know that the name 'binary tree' does not imply
// binary search tree but that is what this is.

#ifndef _TREE_BINARY_SEARCH_TREE_H_
#define _TREE_BINARY_SEARCH_TREE_H_
#include "Tree.h"


template <class T>
class BinaryTree : public Tree<T> {
 public:
  BinaryTree();                             // Default tree constructor
  void Add(T);                              // Adds a value to the tree
  void Remove(T);                           // Removes a value from the tree
  bool Contains(T) const;                   // Searches tree for a value
  T Top() const;                            // Returns the root's value
  T Pop();                                  // Pops the root off and returns value
  size_t Size() const;                      // Returns the number of elements in the tree
  size_t MaxDepth() const;                  // Returns the maximum depth of the tree
  size_t Depth(T) const;                    // Returns the depth of the node with the specified value
  void Print() const;                       // Print's the tree's values using an in-order traversal
  void PrintTop() const;                    // Method to print the top of the tree's references
  class Node {
   public:
    Node();                                 // Default node constructor
    Node(T val);                            // Node constructor with only value
    Node(T val, Node* left_, Node* right_); // Explicit Node constructor
    Node* left;
    Node* right;
    T val;
  };
 private:                                   // Helper methods and root
  Node* root;
  Node* Insert(Node* current, T val);
  Node* Remove(Node* current, T val);
  Node* FindMinFrom(Node* current) const;
  Node* RemoveMinFrom(Node* current);
  bool Contains(Node* current, T val) const;
  void PrintInOrder(Node* current) const;
  size_t Size(Node* current) const;
  size_t MaxDepth(Node* current, size_t curr_depth) const;
  size_t Depth(Node* current, T val, size_t curr_depth) const;
};
#include "BinaryTree.cc"
#endif