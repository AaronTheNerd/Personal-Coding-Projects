class Shape {
  ArrayList<Line> lines;
  float angle;
  Point center;
  int sides;
  
  Shape(Point center_, float radian, int sides_) {
    lines = new ArrayList<Line>();
    center = center_;
    sides = sides_;
    getAngle();
    defineShape(radian);
  }
  Shape(Line edge, int sides_) {
    lines = new ArrayList<Line>();
    lines.add(edge);
    getAngle();
    sides = sides_;
    defineShape(edge);
  }
  void getAngle() {
    angle = 2 * PI / sides;
  }
  void defineShape(float radian) {
    for (int i = 0; i < sides; ++i) {
      lines.add(new Line(
          new Point(center.x - (radian * cos(i * angle)),
                    center.y + (radian * sin(i * angle))),
          new Point(center.x - (radian * cos((i + 1) * angle)),
                    center.y + (radian * sin((i + 1) * angle)))));
    }
  }
  void defineShape(Line edge) {
    Line current_line = edge.flip();
    for (int i = 0; i < sides - 1; ++i) {
      Line line_at_origin = current_line.moveToOrigin();
      Line rotated_line_at_origin = line_at_origin.rotate(-interiorAngle());
      Line new_line = rotated_line_at_origin.translateTo(current_line.start);
      Line flipped = new_line.flip();
      lines.add(flipped);
      current_line = flipped;
    }
  }
  float interiorAngle() {
    return (sides - 2) * PI / sides;
  }
  void show() {
    beginShape();
    for (Line l : lines) {
      vertex(l.end.x, l.end.y);
      vertex(l.start.x, l.start.y);
    }
    endShape();
  }
  void grow() {
    if (lines.get(0).length < 8)
      return;
    ArrayList<Line> nextLines = new ArrayList<Line>();
    for (Line l : lines) {
      Line[] split_line = l.split();
      nextLines.add(split_line[0]);
      nextLines.add(split_line[2]);
      Shape s = new Shape(split_line[1], sides);
      s.show();
      for (Line line : s.lines) {
        if (!line.equals(split_line[1])) {
          nextLines.add(line);
        }
      }
    }
    lines = nextLines;
  }
  void showLines() {
    for (Line l : lines)
      l.show();
  }
}
