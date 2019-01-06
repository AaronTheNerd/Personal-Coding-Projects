// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_GRAPH_H_
#define _PATHFINDING_GRAPH_H_
#include "Node.h"
#include "Edge.h"
#include <vector>
class Graph {
 public:
  Graph();
  Node& getNodeAt(int, int) const;
  std::vector<Edge> getNeighbors(Node);
 private:
  void addNode(int, int);
  void addEdge(Node, Node, int);
  Node start_;
  std::vector<Node> nodes_;
};
#endif