// Written by Aaron Barge
// Copyright 2019

#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
class Tree {
 public:
  Tree(); // Creates an empty Tree
  void Add(int val); // Adds a specific value to the Tree
  int Pop(); // Removes the root of the tree an replaces it
  void Remove(int val); // Removes a specific Node from the tree
  bool Contains(int val); // Returns a boolean based off if that value is contained
  int Top(); // Returns the value of the root
 private:
  class Node {
   public:
    Node(int val); // Creates a Node with no children but contains val
    Node *left_child_;
    Node *right_child_;
    int val_;
  };
  Node* root;
  Node* Insert(Node* current, int val); // Helper method for inserting a Node
  bool Contains(Node* current, int val); // Helper method for finding a Node
  Node* Remove(Node* current, int val); // Helper method for removing a Node
  Node* FindMinFrom(Node* current);
  Node* RemoveMinFrom(Node* current);
};
#endif