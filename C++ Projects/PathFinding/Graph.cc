// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_GRAPH_CC_
#define _PATHFINDING_GRAPH_CC_
#include "Graph.h"
#include <iostream>
#include <string>
#endif

Graph::Graph() {
  nodes_ = new std::vector<Node>();
}
Node Graph::getNodeAt(int x, int y) {
  for (Node n: nodes_)
    if (n.getX() == x && n.getY() == y)
      return n;
  return new Node();
}
std::vector<Edge> getNeighbors(Node n) {

}