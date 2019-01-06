// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_H_
#define _PATHFINDING_NODE_H_
#include "Edge.h"
#include <vector>
class Node {
 public:
  Node();
  Node(int, int);
  inline std::vector<Edge> getNeighbors() { return neighbors_; }
  inline int getX() { return x_; }
  inline int getY() { return y_; }
  void addEdge(Edge);
 private:
  int x_;
  int y_;
  std::vector<Edge> neighbors_;
};
#endif