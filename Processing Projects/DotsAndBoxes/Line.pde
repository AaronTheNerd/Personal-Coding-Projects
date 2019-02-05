
class Line {
  public static final boolean HORIZONTAL = true;
  public static final boolean VERTICAL = false;
  Dot dot_1;
  Dot dot_2;
  Dot center;
  float thickness;
  boolean orientation;
  Player owner;
  
  
  
  Line(Dot d1, Dot d2, boolean an_orientation) {
    dot_1 = d1;
    dot_2 = d2;
    thickness = d1.radius / 2.0;
    orientation = an_orientation;
    owner = null;
    if (orientation == Line.HORIZONTAL)
      center = new Dot(dot_1.x + abs(dot_1.x - dot_2.x) / 2.0, dot_1.y, 0);
    else
      center = new Dot(dot_1.x, dot_1.y + abs(dot_1.y - dot_2.y) / 2.0, 0);
  }
  
  
  
  boolean setOwner(Player p) {
    if (p != null && owner == null) {
      owner = p;
      return true;
    }
    return false;
  }
  
  
  
  boolean equals(Line l) {
    return (dot_1.equals(l.dot_1)
        && dot_2.equals(l.dot_2))
        || (dot_1.equals(l.dot_2)
        && dot_2.equals(l.dot_1));
  }
  
  
  
  void show() {
    if (owner == null)
      show(240, 240, 240);
    else
      show(owner.color_[0], owner.color_[1], owner.color_[2]);
  }
  
  
  
  void show(int c1, int c2, int c3, int c4) {
    fill(c1, c2, c3, c4);
    stroke(c1, c2, c3, c4);
    if (this.orientation == Line.HORIZONTAL) {
      rect(dot_1.x, dot_1.y - thickness / 2.0, abs(dot_1.x - dot_2.x), thickness);
    } else {
      rect(dot_1.x - thickness / 2.0, dot_1.y, thickness, abs(dot_1.y - dot_2.y));
    }
  }
  
  
  
  void show(Player p) {
    if (owner != null)
      return;
    if (p == null) {
      show();
      return;
    }
    if (p.color_ != null)
      show(p.color_[0], p.color_[1], p.color_[2], 50);
    else
      show();
  }
  
  
  
  void show(int c1, int c2, int c3) {
    fill(c1, c2, c3);
    stroke(c1, c2, c3);
    if (this.orientation == Line.HORIZONTAL) {
      rect(dot_1.x, dot_1.y - thickness / 2.0, abs(dot_1.x - dot_2.x), thickness);
    } else {
      rect(dot_1.x - thickness / 2.0, dot_1.y, thickness, abs(dot_1.y - dot_2.y));
    }
  }
}
