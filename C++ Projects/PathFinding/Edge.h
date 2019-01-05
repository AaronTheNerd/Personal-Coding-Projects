// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_EDGE_H_
#define _PATHFINDING_EDGE_H_
#include "Node.h"
class Edge {
 public:
  Edge(Node, int);
  inline Node to() { return to_; }
  inline int weight() { return weight_; }
 private:
  Node to_;
  int weight_;
};
#endif