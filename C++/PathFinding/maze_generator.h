// Written by Aaron Barge
// Copyright 2019
#ifndef _MAZE_GENERATOR_H_
#define _MAZE_GENERATOR_H_
#include "Maze.h"
#include "bitmap_image.hpp"
#include <string>
#endif

bitmap_image Generate(int width, int height, std::string name) {
  bitmap_image image(width, height);
  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      image.set_pixel(x, y, make_colour(255, 255, 255));
    }
  }
  image.save_image(name + ".bmp");
}