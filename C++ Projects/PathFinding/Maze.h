// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_H_
#define _PATHFINDING_MAZE_H_
#include "Node.h"
#include "bitmap_image.hpp"
#include <vector>
#include <string>


class Maze {
 public:
  Maze(std::string filename);
  void makeImage(std::string filename);
  void print() const;
  Node* start;
  Node* end;
  std::vector<std::vector<Node*> > maze;
 private:
  void AssembleMaze(bitmap_image filename);
  bool contained(const int n, const int lower, const int upper) const;
};

#endif