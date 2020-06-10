class Line {
  Point start;
  Point end;
  float length;
  
  Line(Point p1, Point p2) {
    start = p1;
    end = p2;
    length = sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
  }
  Line[] split() {
    Point one_third = new Point(start.x + (end.x - start.x) / 3,
                                start.y + (end.y - start.y) / 3);
    Point two_third = new Point(end.x - (end.x - start.x) / 3,
                                end.y - (end.y - start.y) / 3);
    Line[] ret_lines = {
        new Line(start, one_third),
        new Line(one_third, two_third),
        new Line(two_third, end)
    };
    return ret_lines;
  }
  boolean equals(Line l) {
    return (end.equals(l.end)
        && start.equals(l.start))
        || (end.equals(l.start)
        && start.equals(l.end));
  }
  Line moveToOrigin() {
    return new Line(
        new Point(0, 0),
        new Point(end.x - start.x,
            end.y - start.y));
  }
  Line rotate(float angle) {
    return new Line(
        new Point(0, 0),
        new Point(end.x * cos(angle) - end.y * sin(angle),
            end.x * sin(angle) + end.y * cos(angle)));
  }
  Line translateTo(Point p) {
    return new Line(p,
        new Point(end.x + p.x,
            end.y + p.y));
  }
  Line flip() {
    return new Line(new Point(end.x, end.y), new Point(start.x, start.y));
  }
  void show() {
    stroke(255, 100, 0);
    fill(100, 255, 0);
    start.show();
    fill(255, 0, 100);
    end.show();
    line(start.x, start.y, end.x, end.y);
  }
}
