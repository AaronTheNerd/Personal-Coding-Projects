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
  DepthFirst(m);
  //m.print();
}

bool contains(std::vector<Node*>& nodes, Node* n) {
  for (size_t i = 0; i < nodes.size(); ++i) {
    if (n == nodes[i])
      return true;
  }
  return false;
}

void DepthFirstRecursion(Maze m, std::vector<Node*>& nodes, Node* curr) {
  nodes.push_back(curr);
  if (curr == m.end)
    return;
  for (Node* n : curr->getNeighbors()) {
    if (!contains(nodes, n))
      DepthFirstRecursion(m, nodes, n);
  }
  nodes.pop_back();
  DepthFirstRecursion(m, nodes, nodes.back());
}

void DepthFirst(Maze m) {
  std::vector<Node*> nodes;
  DepthFirstRecursion(m, nodes, m.start);
  ConstructImage(m, nodes);
}

void ConstructImage(Maze m, std::vector<Node*> nodes) {
  bitmap_image image(m.maze.size(), m.maze.size());
  for (size_t x = 0; x < m.maze.size(); ++x) {
    for (size_t y = 0; y < m.maze.size(); ++y) {
      rgb_t color;
      if (contains(nodes, m.maze[x][y])) {
        color = make_colour(255, 0, 0);
      } else if (m.maze[x][y] != NULL) {
        color = make_colour(255, 255, 255);
      } else {
        color = make_colour(0, 0, 0);
      }
      image.set_pixel(x, y, color);
    }
  }
  image.save_image("Solved_Maze.bmp");
}