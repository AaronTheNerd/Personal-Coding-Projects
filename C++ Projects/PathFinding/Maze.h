// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_H_
#define _PATHFINDING_MAZE_H_
#include "Node.h"
#include <vector>
#include <string>


class Maze {
 public:
  Maze(std::string filename);
 private:
  Node* start;
  Node* end;
  void AssembleMaze(std::string filename, int x, int y);
};
#endif