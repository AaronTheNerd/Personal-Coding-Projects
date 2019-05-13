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
  bool operator==(const Node* n) const;
  void setPos(int, int);
  void checkConnections();
  Node* prev;
  std::vector<Node*> neighbors_;
 protected:
  int x_;
  int y_;
};
#endif