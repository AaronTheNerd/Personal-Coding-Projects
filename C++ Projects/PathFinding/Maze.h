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
  Maze(const std::string filename);
  Maze(int width, int height);
  Maze(int width, int height, const std::string name_);
  void makeImage(const std::string filename);
  void print() const;
  std::vector<Node*>& operator[](const size_t index);
  size_t width() const;
  size_t height() const;
  Node* start;
  Node* end;
  std::string name;
  std::vector<std::vector<Node*> > maze;
  static const int MINIMAL_SIZE = 10;
 private:
  void init(int width, int height, const std::string name, const bitmap_image image);
  void AssembleMaze(const bitmap_image file);
  void AssembleMaze();
  void TraverseMaze(const bitmap_image file);
  void TraverseMaze(Node* current, const bitmap_image file);
  bool contained(const int n, const int lower, const int upper) const;
  bool isIntersection(const bitmap_image file, const int x, const int y);
  bool deadEnd(const bitmap_image file, const int x, const int y);
  bool isCorner(const bitmap_image file, const int x, const int y);
};

#endif
