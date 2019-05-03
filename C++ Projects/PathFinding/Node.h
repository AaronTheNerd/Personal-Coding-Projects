// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_H_
#define _PATHFINDING_NODE_H_
#include <vector>


class Node {
 public:
  Node();
  Node(int x, int y);
  inline std::vector<Node*> getNeighbors() const { return neighbors_; }
  inline int getX() const { return x_; }
  inline int getY() const { return y_; }
  bool operator!=(const Node* n) const;
  void addEdge(Node*);
 protected:
  int x_;
  int y_;
  std::vector<Node*> neighbors_;
};
#endif