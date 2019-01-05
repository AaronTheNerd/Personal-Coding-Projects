// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_EDGE_CC_
#define _PATHFINDING_EDGE_CC_
#include "Edge.h"
#endif

Edge::Edge(Node to, int weight) {
  to_ = to;
  if (weight < 0)
    return;
  weight_ = weight;
}