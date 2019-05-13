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
  Maze();
  Maze(std::string filename);
  Maze(int width, int height);
  Maze(int width, int height, std::string name_);
  void makeImage(std::string filename);
  void print() const;
  std::vector<Node*>& operator[](size_t index);
  size_t width() const;
  size_t height() const;
  Node* start;
  Node* end;
  std::string name;
  std::vector<std::vector<Node*> > maze;
  static const int MINIMAL_SIZE = 10;
 private:
  void init(int width, int height, std::string name, bitmap_image image);
  void AssembleMaze(bitmap_image filename);
  void AssembleMaze();
  bool contained(const int n, const int lower, const int upper) const;
};

#endif
