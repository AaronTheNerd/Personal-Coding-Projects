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
  this->start->checkConnections();
  this->end = this->maze[image.width() - 1][image.height() - 1];
}

void Maze::AssembleMaze(bitmap_image bitmap) {
  for (int x = 0; x < bitmap.width(); ++x) {
    for (int y = 0; y < bitmap.height(); ++y) {
      if (bitmap.get_pixel(x, y) == make_colour(0, 0, 0)) {
        this->maze[x][y] = NULL;
        continue;
      }
      this->maze[x][y] = new Node(x, y);
    }
  }
  AssembleMaze();
}
void Maze::AssembleMaze() {
  for (int x = 0; x < this->width(); ++x) {
    for (int y = 0; y < this->height(); ++y) {
      if (this->maze[x][y] == NULL)
        continue;
      for (int x_off = -1; x_off <= 1; ++x_off) {
        for (int y_off = -1; y_off <= 1; ++y_off) {
          if (contained(x + x_off, 0, this->width())
              && contained(y + y_off, 0, this->height())
              && !((x_off == 0) && (y_off == 0))
              && this->maze[x + x_off][y + y_off] != NULL) {
            this->maze[x][y]->neighbors_.push_back(this->maze[x + x_off][y + y_off]);
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
  for (size_t x = 0; x < this->width(); ++x) {
    for (size_t y = 0; y < this->height(); ++y) {
      if (x == 0 && y == 0)
        std::cout << "S";
      else if (x == this->width() - 1 && y == this->height() - 1)
        std::cout << "G";
      else
        std::cout << ((this->maze[x][y] != NULL) ? (" ") : ("#")) << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<Node*>& Maze::operator[] (size_t index) {
  return this->maze[index];
}

size_t Maze::width() const {
  return this->maze.size();
}

size_t Maze::height() const {
  return this->maze[0].size();
}
