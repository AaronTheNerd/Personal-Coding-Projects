// Written by Aaron Barge
// Copyright 2019

#ifndef _C_PLUS_PLUS_PROJECTS_GRAPH_H_
#define _C_PLUS_PLUS_PROJECTS_GRAPH_H_
#include <vector>
class Graph {
 public:
  Graph();
  void AddNode(int node_value);
  void AddLink(int from, int to);
  void RemoveNode(int node_value);
  void RemoveLink(int from, int to);
 private:
  class Node {
   public:
    Node();
    Node(int val_);
    void AddLink(Node* to);
    void RemoveLink(Node* to);
    int val;
    std::vector<Node*> in;
    std::vector<Node*> out;
  };
  Node* origin;
  std::vector<Node*> nodes;
  Node* FindNode(int node_val);
};
#endif