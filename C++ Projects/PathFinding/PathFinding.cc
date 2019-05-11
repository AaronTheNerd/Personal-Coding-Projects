// Written by Aaron Barge
// Copyright 2019
// Huge thanks to Arash Partow for making bitmap_image.hpp
// Which I will be using in this project to read and write to .bmp file
// This project will take a bitmap file of black and white pixels.
// Create a maze where the white spots are paths and the black pixels are walls
// Then return a bitmap with the path found by each function in the form:
// <name>.<function>.bmp
// In order to use this project you will need to create a bitmap named
// maze.bmp or just change the name in this file.
// You must make sure that the upper-left and bottom-right
// pixels are both white

#include "Maze.h"
#include <string>
#include <queue>
#include <vector>

void DepthFirst(Maze m);
void Djikstra(Maze m);
void AStar(Maze m);
void ConstructImage(Maze m, std::vector<Node*> nodes);

int main(int argc, char** argv) {
  Maze m(std::string("maze.bmp"));
  m.print();
  DepthFirst(m);
}

bool contains(std::vector<Node*>& nodes, Node* n) {
  if (n == NULL)
    return false;
  for (size_t i = 0; i < nodes.size(); ++i) {
    if (n == nodes[i])
      return true;
  }
  return false;
}

void DepthFirstRecursion(Maze m, std::vector<Node*>& path, std::vector<Node*>& checked, Node* curr) {
  path.push_back(curr);
  checked.push_back(curr);
  if (curr == m.end) {
    std::cout << "The end of the maze was found!" << std::endl;
    return;
  }
  for (Node* n : curr->neighbors_) {
    if (!contains(checked, n)) {
      return DepthFirstRecursion(m, path, checked, n);
    }
  }
  path.pop_back();
  return DepthFirstRecursion(m, path, checked, path.back());
}

void DepthFirst(Maze m) {
  std::vector<Node*> path, checked;
  DepthFirstRecursion(m, path, checked, m.start);
  std::cout << "Path nodes" << std::endl;
  for (Node* n : path)
    std::cout << n->getX() << ", " << n->getY() << std::endl;
  ConstructImage(m, path);
}

void ConstructImage(Maze m, std::vector<Node*> nodes) {
  bitmap_image image(m.width(), m.height());
  for (size_t x = 0; x < m.width(); ++x) {
    for (size_t y = 0; y < m.height(); ++y) {
      rgb_t color;
      if (m[x][y] == NULL) {
        color = make_colour(0, 0, 0);
      } else if (contains(nodes, m[x][y])) {
        color = make_colour(255, 0, 0);
      } else {
        color = make_colour(255, 255, 255);
      }
      image.set_pixel(x, y, color);
    }
  }
  image.save_image("Solved_Maze.bmp");
}