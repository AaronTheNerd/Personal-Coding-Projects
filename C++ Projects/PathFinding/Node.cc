// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_CC_
#define _PATHFINDING_NODE_CC_
#include "Node.h"
#endif
Node::Node() {
  neighbors_ = std::vector<Edge>();
  x_ = 0;
  y_ = 0;
}
Node::Node(int x, int y) {
  Node();
  x_ = x;
  y_ = y;
}
void Node::addEdge(Edge e) {
  neighbors_.push_back(e);
}