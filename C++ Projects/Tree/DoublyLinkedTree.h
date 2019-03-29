// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_DOUBLY_LINKED_TREE_H_
#define _TREE_DOUBLY_LINKED_TREE_H_
#include "BinaryTree.h"


template <class T>
class DLTree : public BinaryTree {
 public:
  DLTree(); // Default tree constructor
  ~DLTree();
  void Add(T); // Adds a value to the tree
  void Remove(T); // Removes a value from the tree
  bool Contains(T) const; // Searches tree for a value
  T Top() const; // Returns the root's value
  T Pop(); // Pops the root off and returns value
  size_t Size() const; // Returns the number of elements in the tree
  size_t MaxDepth() const; // Returns the maximum depth of the tree
  size_t Depth(T) const; // Returns the depth of the node with the specified value
                         // It is good to note that this is fairly inefficient compared to
                         // It's parent's implementation. Where the parent's implementation
                         // Keeps track of the current depth while searching this one does not
                         // and instead just uses the parent pointer to go to the root
  void Print() const; // Print's the tree's values using an in-order traversal
  void PrintTop() const; // Method to print the top of the tree's references
 protected:
  class Node {
   public:
     Node(); // Default node constructor
     ~Node();
     Node(T val); // Node constructor with only value
     Node(T val, Node *left, Node *right, Node *parent); // Explicit Node constructor
     Node *left;
     Node *right;
     Node *parent;
     T val;
  }; // Helper methods and root
  Node* root;
  void DestroyTree(Node*);
  Node* Insert(Node*, Node*, T);
  Node* Remove(Node*, T);
  size_t Depth(Node*, T) const;
  Node* FindMinFrom(Node*) const;
  Node* RemoveMinFrom(Node*);
};
#include "DoublyLinkedTree.cc"
#endif