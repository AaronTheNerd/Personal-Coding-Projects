// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_MAZE_CC_
#define _PATHFINDING_MAZE_CC_
#include "Maze.h"
#endif
Maze::Maze(std::string filename, int width, int height) {
  
  std::ifstream img(filename);
  std::ofstream solved_img_1("SolvedMazeAStar.ppm");
  std::ofstream solved_img_2("SolvedMazeDijkstra.ppm");
  initGraph(img, width, height);
  ASolve(solved_img_1);
  DijkstraSolve(solved_img_2);
}
void Maze::ASolve(std::ofstream& new_img) {

}
void Maze::DijkstraSolve(std::ofstream& new_img) {

}
void initGraph(const std::ifstream&, int width, int height) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      
    }
  }
}