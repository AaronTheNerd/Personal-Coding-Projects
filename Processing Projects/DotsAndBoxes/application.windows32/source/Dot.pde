class Dot {
  float x, y, radius;
  float margin, height_gap, dot_gap;
  Dot(float x_, float y_, float radius_) {
    x = x_;
    y = y_;
    radius = radius_;
  }
  void addMargin(float margin_) {
    margin = margin_;
  }
  void addHeight(float height_gap_) {
    height_gap = height_gap_;
  }
  void addGap(float dot_gap_) {
    dot_gap = dot_gap_;
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
  void print() {
    println("  X: " + (x - margin) / dot_gap + " , Y: " + (y - height_gap) / dot_gap);
  }
}
