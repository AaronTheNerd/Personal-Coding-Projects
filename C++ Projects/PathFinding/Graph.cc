// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_GRAPH_CC_
#define _PATHFINDING_GRAPH_CC_
#include "Graph.h"
#include <iostream>
#include <string>
#endif

Graph::Graph() {
  nodes_ = std::vector<Node>();
}
Node& Graph::getNodeAt(int x, int y) const {
  for (Node n: nodes_)
    if (n.getX() == x && n.getY() == y)
      return n;
  Node n;
  return n;
}
std::vector<Edge> Graph::getNeighbors(Node n) {
  return this->getNodeAt(n.getX(), n.getY()).getNeighbors();
}
void Graph::addNode(int x, int y) {
  Node n(x, y);
  nodes_.push_back(n);
}
void Graph::Connect(Node from, Node to, int weight) {
  Edge e1(to, weight);
  from.addEdge(e1);
  Edge e2(from, weight);
  to.addEdge(e2);
}