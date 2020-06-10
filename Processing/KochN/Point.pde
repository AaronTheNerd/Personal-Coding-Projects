class Point {
  float x;
  float y;
  Point(float x_, float y_) {
    x = x_;
    y = y_;
  }
  void show() {
    ellipse(x, y, 10, 10);
    fill(0);
  }
  boolean equals(Point p) {
    return x == p.x
        && y == p.y;
  }
}
