class Box {
  Player owner;
  Line[] borders;
  
  Box(Line l1, Line l2, Line l3, Line l4) {
    borders = new Line[4];
    borders[0] = l1;
    borders[1] = l2;
    borders[2] = l3;
    borders[3] = l4;
    owner = null;
  }
  
  boolean CheckIfOwned(Player current) {
    for (Line l : borders)
      if (l.owner == null)
        return false;
    owner = current;
    current.claimed.add(this);
    show();
    println("A box has been claimed");
    return true;
  }
  
  boolean contains(Line line) {
    for (Line l : borders) {
      if (l.equals(line))
        return true;
    }
    return false;
  }
  
  float minX() {
    float[] xs = new float[4];
    for (int i = 0; i < xs.length; ++i)
      xs[i] = borders[i].dot_1.x;
    return min(xs);
  }
  float minY() {
    float[] ys = new float[4];
    for (int i = 0; i < ys.length; ++i)
      ys[i] = borders[i].dot_1.y;
    return min(ys);
  }
  float maxX() {
    float[] xs = new float[4];
    for (int i = 0; i < xs.length; ++i)
      xs[i] = borders[i].dot_1.x;
    return max(xs);
  }
  float maxY() {
    float[] ys = new float[4];
    for (int i = 0; i < ys.length; ++i)
      ys[i] = borders[i].dot_1.y;
    return max(ys);
  }
  
  void show() {
    fill(owner.color_[0], owner.color_[1], owner.color_[2], 150);
    rectMode(CORNERS);
    rect(minX(), minY(), maxX(), maxY());
    rectMode(CORNER);
  }
}
