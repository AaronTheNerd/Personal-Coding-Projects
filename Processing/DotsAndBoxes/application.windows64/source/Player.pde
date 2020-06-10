// Written by Aaron Barge
// Copyright 2019
class Player {
  String name;
  int[] color_;
  ArrayList<Box> claimed;
  
  
  
  Player(String name_) {
    name = name_;
    claimed = new ArrayList<Box>();
  }
  
  
  
  void SetColor(int color_1, int color_2, int color_3) {
    color_ = new int[3];
    color_[0] = color_1;
    color_[1] = color_2;
    color_[2] = color_3;
  }
}
