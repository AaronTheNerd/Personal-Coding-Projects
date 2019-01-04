// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_H_
#define _PATHFINDING_MAZE_H_
#include "Graph.h"
#include <string>
class Maze : public Graph {
 public:
  Maze(std::string);
  void ASolve();
  void DijkstraSolve();
};
#endif