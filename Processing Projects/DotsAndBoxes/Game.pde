// Written by Aaron Barge
// Copyright 2019
class Game {
  Player current;
  Player player1;
  Player player2;
  int x,y;
  float dot_gap;
  float margin, height_gap;
  float radius;
  Dot[][] dots;
  Line[] lines;
  int current_line;
  Box[][] boxes;
  
  
  
  Game(int x_, int y_) {
    x = x_;
    y = y_;
    generateBounds();
    dots = new Dot[x+1][y+1];
    lines = new Line[(2 * x * y) + x + y];
    boxes = new Box[x][y];
    background(137, 189, 255);
    initDots();
    current_line = 0;
    initBoxes();
    current = player1 = player2 = null;
  }
  
  
  
  private void generateBounds() {
    margin = width / 20.0;
    height_gap = height / 20.0;
    float dot_gap_x = (width - 2.0 * margin) / float(x + 1);
    float dot_gap_y = (height - 2.0 * height_gap) / float(y + 1);
    dot_gap = min(dot_gap_x, dot_gap_y);
    margin = (width - (dot_gap * x)) / 2.0;
    height_gap = (height - (dot_gap * y)) / 2.0;
    radius = dot_gap / 7.5;
  }
  
  
  
  private void initDots() {
    for (float x_ = margin, i = 0; i <= x; x_ += dot_gap, i++) {
      for (float y_ = height_gap, j = 0; j <= y; y_ += dot_gap, j++) {
        dots[int(i)][int(j)] = new Dot(x_, y_, radius);
      }
    }
  }
  // I know this next method is kind of messy but
  // It does make sure that there is only one instance of each line
  // And that when that instance is changed it changes the box's instance
  private void initBoxes() {
    for (int x_ = 0; x_ < x; ++x_) {
      for (int y_ = 0; y_ < y; ++y_) {
        Line top;
        if (y_ == 0) {
          top = new Line(dots[x_][y_], dots[x_ + 1][y_], Line.HORIZONTAL);
          add(top);
        } else {
          top = findLine(dots[x_][y_], dots[x_ + 1][y_]);
        }
        Line left;
        if (x_ == 0) {
          left = new Line(dots[x_][y_], dots[x_][y_ + 1], Line.VERTICAL);
          add(left);
        } else {
          left = findLine(dots[x_][y_], dots[x_][y_ + 1]);
        }
        Line right = new Line(dots[x_ + 1][y_], dots[x_ + 1][y_ + 1], Line.VERTICAL);
        add(right);
        Line bottom = new Line(dots[x_][y_ + 1], dots[x_ + 1][y_ + 1], Line.HORIZONTAL);
        add(bottom);
        boxes[x_][y_] = new Box(top, left, right, bottom);
      }
    }
  }
  
  
  
  private void add(Line l) {
    lines[current_line] = l;
    current_line++;
  }
  
  
  
  private Line findLine(Dot d1, Dot d2) {
    Line looking = new Line(d1, d2, Line.HORIZONTAL);
    for (int i = 0; i < current_line; ++i)
      if (lines[i].equals(looking))
        return lines[i];
    return null;
  }
  
  
  
  void AddPlayer(Player p) {
    if (current == null)
      current = p;
    if (player1 == null)
      player1 = p;
    else
      player2 = p;
  }
  
  
  
  Line FindClosestLine(float x_, float y_) {
    Line closest = lines[0];
    for (int i = 1; i < lines.length; ++i) {
      if ((x_ - lines[i].center.x) * (x_ - lines[i].center.x)
        + (y_ - lines[i].center.y) * (y_ - lines[i].center.y)
        < (x_ - closest.center.x) * (x_ - closest.center.x)
        + (y_ - closest.center.y) * (y_ - closest.center.y))
        closest = lines[i];
    }
    return closest;
  }
  
  
  
  boolean checkForBoxes(Line l) {
    boolean result = false;
    for (int x_ = 0; x_ < x; ++x_) {
      for (int y_ = 0; y_ < y; ++y_) {
        if (boxes[x_][y_].contains(l))
          if (result == true)
            boxes[x_][y_].CheckIfOwned(current);
          else
            result = boxes[x_][y_].CheckIfOwned(current);
      }
    }
    return result;
  }
  
  
  
  void switchPlayer() {
    current = (current.equals(player1)) ? player2 : player1;
  }
  
  
  
  void show() {
    checkWin();
    showLines();
    showDots();
  }
  
  
  
  void showLines() {
    Line closest = FindClosestLine(mouseX, mouseY);
    for (Line l : lines) {
      if (current != null) {
        if (l.equals(closest))
          l.show(current);
        else
          l.show();
      }
      else
        l.show();
    }
  }
  
  
  
  void showDots() {
    for (Dot[] ds : dots)
      for (Dot d : ds)
          d.show();
  }
  
  
  
  void checkWin() {
    if (player1 != null && player2 != null) {
      if (player1.claimed.size() + player2.claimed.size() == x * y) {
        textSize(height_gap / 2);
        textAlign(CENTER, CENTER);
        text("Game over", width/2, height_gap / 2);
        if (player1.claimed.size() > player2.claimed.size())
          text(player1.name + " has won!", width / 2, height - height_gap / 2);
        else if(player2.claimed.size() > player1.claimed.size())
          text(player2.name + " has won!", width / 2, height - height_gap / 2);
        else
          text("It's a tie!", width / 2, height - height_gap / 2);
      }
    }
  }
}
