// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_H_
#define _PATHFINDING_NODE_H_
#include <vector>


class Node {
 public:
  Node();
  Node(int x, int y);
  inline std::vector<Node*> getNeighbors() { return neighbors_; }
  inline int getX() { return x_; }
  inline int getY() { return y_; }
  void addEdge(Node*);
 private:
  int x_;
  int y_;
  std::vector<Node*> neighbors_;
};
#endif