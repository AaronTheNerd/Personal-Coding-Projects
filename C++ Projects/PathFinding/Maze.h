// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_H_
#define _PATHFINDING_MAZE_H_
#include "Graph.h"
#include <string>
#include <fstream>
class Maze : public Graph {
 public:
  Maze(std::string, int, int);
  void ASolve(std::ofstream&);
  void DijkstraSolve(std::ofstream&);
 private:
  void initGraph(const std::ifstream&, int, int);
};
#endif