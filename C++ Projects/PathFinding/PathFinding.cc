// Written by Aaron Barge
// Copyright 2019
// Huge thanks to Arash Partow for making bitmap_image.hpp
// Which I will be using in this project to read and write to .bmp file
// This project will either take a bitmap file of black and white pixels.
// Create a maze where the white spots are paths and the black pixels are walls
// Then return a bitmap with the path found by each function
// You must make sure that the upper-left and bottom-right
// pixels are both white
// Or can randomly generate a maze based off of given dimensions
// and/or a file name without the extension
// Uses:
//   Input:
//     ./<executable> <bitmap_maze>.bmp
//   Output:
//     <bitmap_maze>.<algorithm>.bmp
//
//   Input:
//     ./<executable> <width> <height>
//   Output:
//     maze.bmp
//     maze.<algorithm>.bmp
//
//   Input:
//     ./<executable> <width> <height> <name>
//   Output:
//     <name>.bmp
//     <name>.<algorithm>.bmp

#include "Maze.h"
#include <string>
#include <queue>
#include <stack>
#include <vector>

void DepthFirst(Maze m);
void Djikstra(Maze m);
void AStar(Maze m);
std::vector<Node*> DecodePath(Maze m);
void ConstructImage(Maze m, std::vector<Node*> path, std::string name);

int main(int argc, char** argv) {
  Maze m;
  switch (argc) {
    case 2:
      m = Maze(argv[1]);
      break;
    case 3:
      int width, height;
      try {
        width = int(argv[1]);
        height = int(argv[2]);
      } catch (...) {
        std::cout << "Please enter valid integer dimensions" << std::endl;
        return 0;
      }
      m = Maze(width, height);
      break;
    case 4:
      int width, height;
      try {
        width = int(argv[1]);
        height = int(argv[2]);
      } catch (...) {
        std::cout << "Please enter valid integer dimensions" << std::endl;
        return 0;
      }
      m = Maze(width, height, argv[3]);
      break;
    default:
      std::cout << "Please enter either the name of your maze bitmap or the dimensions of your maze" << std::endl;
      break;
  }
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

void DepthFirst(Maze m) {
  std::vector<Node*> checked;
  std::stack<Node*> stack;
  stack.push(m.start);
  while (!stack.empty()) {
    Node* curr = stack.top();
    if (curr == m.end) {
      checked.push_back(curr);
      break;
    }
    stack.pop();
    checked.push_back(curr);
    for (Node* n : curr->neighbors_) {
      if (!contains(checked, n)) {
        stack.push(n);
        n->prev = curr;
      }
    }
  }
  ConstructImage(m, DecodePath(m), "DFS");
}

std::vector<Node*> DecodePath(Maze m) {
  std::vector<Node*> path;
  Node* curr = m.end;
  while (curr != NULL) {
    path.push_back(curr);
    curr = curr->prev;
  }
  return path;
}

void ConstructImage(Maze m, std::vector<Node*> nodes, std::string name) {
  bitmap_image image(m.width(), m.height());
  for (size_t x = 0; x < m.width(); ++x) {
    for (size_t y = 0; y < m.height(); ++y) {
      rgb_t color;
      if (m[x][y] == NULL) {
        color = make_colour(0, 0, 0);
      } else {
        color = make_colour(255, 255, 255);
      }
      image.set_pixel(x, y, color);
    }
  }
  for (size_t i = 0; i < nodes.size(); ++i) {
    image.set_pixel(nodes[i]->getX(), nodes[i]->getY(), make_colour((1.0 * (nodes.size() - i) / nodes.size()) * 255, 0, (1.0 * i / nodes.size()) * 255));
  }
  image.save_image(m.name + "." + name + ".bmp");
}
