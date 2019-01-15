// Written by Aaron Barge
// Copyright 2019
// Finished on January 15th
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//  This is my third attempt making a Koch fractal in Processing
//  Both of the first 2 worked how they should
//  However I felt like it could be done better
//  So for this version it is controlled by the spacebar
//  and the number of sides can be changed through a variable
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
Shape s;
int sides = 3;
void setup() {
  size(1500, 1500);
  background(255);
  stroke(0);
  fill(0);
  Point center = new Point(width / 2, height / 2);
  float length = 400;
  s = new Shape(center, length, sides);
  fill(0);
  s.show();
}
void draw() {
}
void keyPressed() {
  if (key == ' ')
    s.grow();
}
