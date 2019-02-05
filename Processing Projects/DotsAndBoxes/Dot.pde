// Written by Aaron Barge
// Copyright 2019
class Dot {
  float x, y, radius;
  
  
  
  Dot(float x_, float y_, float radius_) {
    x = x_;
    y = y_;
    radius = radius_;
  }
  
  
  
  void show() {
    stroke(255);
    fill(255);
    ellipse(x, y, radius, radius);
  }
  
  
  
  boolean equals(Dot d) {
    return x == d.x
        && y == d.y;
  }
}
