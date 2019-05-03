// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_CC_
#define _PATHFINDING_MAZE_CC_
#include "Maze.h"
#include "bitmap_image.hpp"
#include <iostream>
#include <string>
#endif


Maze::Maze(std::string filename) {
  bitmap_image image(filename);
  this->maze.resize(image.width(), std::vector<Node*>(image.height(), NULL));
  AssembleMaze(image);
  this->start = this->maze[0][0];
  this->end = this->maze[image.width() - 1][image.height() - 1];
}

void Maze::AssembleMaze(bitmap_image bitmap) {
  for (int x = 0; x < bitmap.width(); ++x) {
    for (int y = 0; y < bitmap.height(); ++y) {
      if (bitmap.get_pixel(x, y) == make_colour(0, 0, 0))
        continue;
      this->maze[x][y] = new Node(x, y);
      for (int x_off = -1; x_off <= 1; ++x_off) {
        for (int y_off = -1; y_off <= 1; ++y_off) {
          if (contained(x + x_off, 0, bitmap.width())
              && contained(y + y_off, 0, bitmap.height())
              && ((x_off != 0) || (y_off != 0))
              && bitmap.get_pixel(x, y) != make_colour(0, 0, 0)) {
            this->maze[x][y]->getNeighbors().push_back(this->maze[x + x_off][y + y_off]);
          }
        }
      }
    }
  }
}

bool Maze::contained(const int n, const int lower, const int upper) const {
  return (n >= lower && n < upper);
}

void Maze::print() const {
  for (size_t x = 0; x < this->maze.size(); ++x) {
    for (size_t y = 0; y < this->maze[x].size(); ++y) {
      std::cout << ((this->maze[x][y] != NULL) ? (" ") : ("X")) << " ";
    }
    std::cout << std::endl;
  }
}