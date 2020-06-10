// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_CC_
#define _PATHFINDING_NODE_CC_
#include "Node.h"
#include <iostream>
#endif


Node::Node() {
  neighbors_ = std::vector<Edge>();
  prev = NULL;
  x_ = 0;
  y_ = 0;
}

Node::Node(int x, int y) {
  neighbors_ = std::vector<Edge>();
  prev = NULL;
  x_ = x;
  y_ = y;
}

void Node::setPos(int x, int y) {
  x_ = x;
  y_ = y;
}

void Node::checkConnections() const {
  std::cout << "The connections of the node at: " << this->x_ << ", " << this->y_ << std::endl;
  for (Edge e : neighbors_)
    std::cout << e->x_ << ", " << e->y_ << std::endl;
}

void Node::addEdge(Node* to, int weight) {
  if (!this->hasNeighbor(to))
    this->neighbors_.push_back(Edge(to, weight));
}

bool Node::hasNeighbor(Node* n) const {
  for (size_t i = 0; i < this->neighbors_.size(); ++i)
    if (n == this->neighbors_[i].to)
      return true;
  return false;
}

bool Node::operator!=(const Node* n) const {
  return !(this == n);
}

bool Node::operator==(const Node* n) const {
  return this->x_ == n->x_ && this->y_ == n->y_;
}