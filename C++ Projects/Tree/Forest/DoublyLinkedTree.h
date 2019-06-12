// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_DOUBLY_LINKED_TREE_H_
#define _TREE_DOUBLY_LINKED_TREE_H_
#include "BinaryTree.h"


template <class T>
class DLTree : public Tree<T> {
 public:
  DLTree();                                          // Default tree constructor
  ~DLTree();                                         // Tree desturctor
  void Add(T);                                       // Adds a value to the tree
  void Remove(T);                                    // Removes a value from the tree
  bool Contains(T) const;                            // Searches tree for a value
  T Top() const;                                     // Returns the root's value
  T Pop();                                           // Pops the root off and returns value
  unsigned int Size() const;                         // Returns the number of elements in the tree
  unsigned int MaxDepth() const;                     // Returns the maximum depth of the tree
  unsigned int Depth(T) const;                       // Returns the depth of the node with the specified value
                                                     // It is good to note that this is fairly inefficient compared to
                                                     // binary tree's implementation. Where the binary tree's implementation
                                                     // Keeps track of the current depth while searching this one does not
                                                     // and instead just uses the parent edge to go to the root
  void Print() const;                                // Print's the tree's values using an in-order traversal
  void PrintTop() const;                             // Method to print the top of the tree's references
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
    Node();                                          // Default node constructor
    Node(T val);                                     // Node constructor with only value
    Node(T val, Edge left, Edge right, Edge parent); // Explicit Node constructor
    ~Node();                                         // Node destructor
    Edge left;
    Edge right;
    Edge parent;
    T val;
  };                                                 // Helper methods and root
  Node* root;
  void DestroyTree(Node*);
  Node* Insert(Node*, Node*, T);
  Node* Remove(Node*, T);
  bool Contains(Node*, T) const;
  unsigned int Depth(Node*, T) const;
  Node* FindMinFrom(Node*) const;
  Node* RemoveMinFrom(Node*);
  void PrintInOrder(Node*) const;
};
#include "DoublyLinkedTree.cc"
#endif