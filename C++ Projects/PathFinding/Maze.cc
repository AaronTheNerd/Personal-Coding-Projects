// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_CC_
#define _PATHFINDING_MAZE_CC_
#include "Maze.h"
#include "maze_generator.h"
#include "bitmap_image.hpp"
#include <iostream>
#include <string>
#endif

Maze::Maze() {}

Maze::Maze(std::string filename) {
  std::string name = filename.substr(0, filename.find("."));
  bitmap_image image(filename);
  init(image.width(), image.height(), name, image);
}

Maze::Maze(int width, int height) {
  width = width < MINIMAL_SIZE ? MINIMAL_SIZE : width;
  height = height < MINIMAL_SIZE ? MINIMAL_SIZE : height;
  bitmap_image image = Generate(width, height, "maze");
  init(width, height, "maze", image);
}

Maze::Maze(int width, int height, std::string name) {
  width = width < MINIMAL_SIZE ? MINIMAL_SIZE : width;
  height = height < MINIMAL_SIZE ? MINIMAL_SIZE : height;
  bitmap_image image = Generate(width, height, name);
  init(width, height, name, image);
}

void Maze::init(int width, int height, std::string name, bitmap_image image) {
  this->name = name;
  this->maze.resize(width, std::vector<Node*>(height, NULL));
  TraverseMaze(image);
  this->start = this->maze[0][0];
  this->end = this->maze[width - 1][height - 1];
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
              && !(y_off == x_off || y_off == -x_off)
              && this->maze[x + x_off][y + y_off] != NULL) {
            this->maze[x][y]->neighbors_.push_back(this->maze[x + x_off][y + y_off]);
          }
        }
      }
    }
  }
}

void Maze::TraverseMaze(bitmap_image file) {
  this->maze[0][0] = new Node(0, 0);
  TraverseMaze(this->maze[0][0], file);
}

void Maze::TraverseMaze(Node* current, bitmap_image file) {
  int x = current->getX();
  int y = current->getY();
  
}

bool Maze::contained(const int n, const int lower, const int upper) const {
  return (n >= lower && n < upper);
}

bool Maze::isIntersection(bitmap_image file, int x, int y) {
  int count = 0;
  if (contained(x + 1, 0, file.width)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x + 1, y))
      count++;
  }
  if (contained(x - 1, 0, file.width)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x - 1, y))
      count++;
  }
  if (contained(y + 1, 0, file.height)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x, y + 1))
      count++;
  }
  if (contained(y - 1, 0, file.height)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x, y - 1))
      count ++;
  }
  return count >= 3;
}

bool Maze::deadEnd(bitmap_image file, int x, int y) {
  int count = 0;
  if (contained(x + 1, 0, file.width)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x + 1, y))
      count++;
  }
  if (contained(x - 1, 0, file.width)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x - 1, y))
      count++;
  }
  if (contained(y + 1, 0, file.height)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x, y + 1))
      count++;
  }
  if (contained(y - 1, 0, file.height)) {
    if (make_colour(255, 255, 255) == file.get_pixel(x, y - 1))
      count ++;
  }
  return count <= 1;
}

bool Maze::isCorner(bitmap_image file, int x, int y) {
  return ();
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
