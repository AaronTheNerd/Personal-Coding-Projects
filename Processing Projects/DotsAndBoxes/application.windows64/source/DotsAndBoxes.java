import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class DotsAndBoxes extends PApplet {

Game dots_and_boxes;



public void setup() {
  
  dots_and_boxes = new Game(5, 3);
  dots_and_boxes.show();
  setupPlayers("Aaron", "Jess");
}



public void setupPlayers(String player1, String player2) {
  Player player_1 = new Player(player1);
  player_1.SetColor(0, 50, 255);
  Player player_2 = new Player(player2);
  player_2.SetColor(255, 0, 0);
  dots_and_boxes.AddPlayer(player_1);
  dots_and_boxes.AddPlayer(player_2);
}



public void draw() {
  dots_and_boxes.show();
}



public void mouseClicked() {
  Line l = dots_and_boxes.FindClosestLine(mouseX, mouseY);
  boolean line_changed = l.setOwner(dots_and_boxes.current);
  if (!line_changed)
    return;
  boolean box_made = dots_and_boxes.checkForBoxes(l);
  if (!box_made)
    dots_and_boxes.switchPlayer();
}
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
  
  
  
  public boolean CheckIfOwned(Player current) {
    for (Line l : borders)
      if (l.owner == null)
        return false;
    owner = current;
    current.claimed.add(this);
    show();
    return true;
  }
  
  
  
  public boolean contains(Line line) {
    for (Line l : borders) {
      if (l.equals(line))
        return true;
    }
    return false;
  }
  
  
  
  public float minX() {
    float[] xs = new float[4];
    for (int i = 0; i < xs.length; ++i)
      xs[i] = borders[i].dot_1.x;
    return min(xs);
  }
  
  
  
  public float minY() {
    float[] ys = new float[4];
    for (int i = 0; i < ys.length; ++i)
      ys[i] = borders[i].dot_1.y;
    return min(ys);
  }
  
  
  
  public float maxX() {
    float[] xs = new float[4];
    for (int i = 0; i < xs.length; ++i)
      xs[i] = borders[i].dot_1.x;
    return max(xs);
  }
  
  
  
  public float maxY() {
    float[] ys = new float[4];
    for (int i = 0; i < ys.length; ++i)
      ys[i] = borders[i].dot_1.y;
    return max(ys);
  }
  
  
  
  public void show() {
    fill(owner.color_[0], owner.color_[1], owner.color_[2], 150);
    rectMode(CORNERS);
    rect(minX(), minY(), maxX(), maxY());
    rectMode(CORNER);
  }
}
class Dot {
  float x, y, radius;
  
  
  
  Dot(float x_, float y_, float radius_) {
    x = x_;
    y = y_;
    radius = radius_;
  }
  
  
  
  public void show() {
    stroke(255);
    fill(255);
    ellipse(x, y, radius, radius);
  }
  
  
  
  public boolean equals(Dot d) {
    return x == d.x
        && y == d.y;
  }
}
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
  
  
  
  public void generateBounds() {
    margin = width / 20.0f;
    height_gap = height / 20.0f;
    float dot_gap_x = (width - 2.0f * margin) / PApplet.parseFloat(x + 1);
    float dot_gap_y = (height - 2.0f * height_gap) / PApplet.parseFloat(y + 1);
    dot_gap = min(dot_gap_x, dot_gap_y);
    margin = (width - (dot_gap * x)) / 2.0f;
    height_gap = (height - (dot_gap * y)) / 2.0f;
    radius = dot_gap / 7.5f;
  }
  
  
  
  public void initDots() {
    for (float x_ = margin, i = 0; i <= x; x_ += dot_gap, i++) {
      for (float y_ = height_gap, j = 0; j <= y; y_ += dot_gap, j++) {
        dots[PApplet.parseInt(i)][PApplet.parseInt(j)] = new Dot(x_, y_, radius);
      }
    }
  }
  
  
  
  public void initBoxes() {
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
  
  
  
  public void add(Line l) {
    lines[current_line] = l;
    current_line++;
  }
  
  
  
  public Line findLine(Dot d1, Dot d2) {
    Line looking = new Line(d1, d2, Line.HORIZONTAL);
    for (int i = 0; i < current_line; ++i)
      if (lines[i].equals(looking))
        return lines[i];
    return null;
  }
  
  
  
  public void AddPlayer(Player p) {
    if (current == null)
      current = p;
    if (player1 == null)
      player1 = p;
    else
      player2 = p;
  }
  
  
  
  public Line FindClosestLine(float x_, float y_) {
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
  
  
  
  public boolean checkForBoxes(Line l) {
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
  
  
  
  public void switchPlayer() {
    current = (current.equals(player1)) ? player2 : player1;
  }
  
  
  
  public void show() {
    checkWin();
    showLines();
    showDots();
  }
  
  
  
  public void showLines() {
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
  
  
  
  public void showDots() {
    for (Dot[] ds : dots)
      for (Dot d : ds)
          d.show();
  }
  
  
  
  public void checkWin() {
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
    thickness = d1.radius / 2.0f;
    orientation = an_orientation;
    owner = null;
    if (orientation == Line.HORIZONTAL)
      center = new Dot(dot_1.x + abs(dot_1.x - dot_2.x) / 2.0f, dot_1.y, 0);
    else
      center = new Dot(dot_1.x, dot_1.y + abs(dot_1.y - dot_2.y) / 2.0f, 0);
  }
  
  
  
  public boolean setOwner(Player p) {
    if (p != null && owner == null) {
      owner = p;
      return true;
    }
    return false;
  }
  
  
  
  public boolean equals(Line l) {
    return (dot_1.equals(l.dot_1)
        && dot_2.equals(l.dot_2))
        || (dot_1.equals(l.dot_2)
        && dot_2.equals(l.dot_1));
  }
  
  
  
  public void show() {
    if (owner == null)
      show(240, 240, 240);
    else
      show(owner.color_[0], owner.color_[1], owner.color_[2]);
  }
  
  
  
  public void show(int c1, int c2, int c3, int c4) {
    fill(c1, c2, c3, c4);
    stroke(c1, c2, c3, c4);
    if (this.orientation == Line.HORIZONTAL) {
      rect(dot_1.x, dot_1.y - thickness / 2.0f, abs(dot_1.x - dot_2.x), thickness);
    } else {
      rect(dot_1.x - thickness / 2.0f, dot_1.y, thickness, abs(dot_1.y - dot_2.y));
    }
  }
  
  
  
  public void show(Player p) {
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
  
  
  
  public void show(int c1, int c2, int c3) {
    fill(c1, c2, c3);
    stroke(c1, c2, c3);
    if (this.orientation == Line.HORIZONTAL) {
      rect(dot_1.x, dot_1.y - thickness / 2.0f, abs(dot_1.x - dot_2.x), thickness);
    } else {
      rect(dot_1.x - thickness / 2.0f, dot_1.y, thickness, abs(dot_1.y - dot_2.y));
    }
  }
}
class Player {
  String name;
  int[] color_;
  ArrayList<Box> claimed;
  
  
  
  Player(String name_) {
    name = name_;
    claimed = new ArrayList<Box>();
  }
  
  
  
  public void SetColor(int color_1, int color_2, int color_3) {
    color_ = new int[3];
    color_[0] = color_1;
    color_[1] = color_2;
    color_[2] = color_3;
  }
}
  public void settings() {  fullScreen(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--hide-stop", "DotsAndBoxes" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
