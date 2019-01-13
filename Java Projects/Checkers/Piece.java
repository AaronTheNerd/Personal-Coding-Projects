import javax.awt.Color;
public class Piece {
  Player owner;
  int x, y;
  boolean king;

  public Piece(int x_, int y_, Player owner_) {
    this.x = (x_ >= 0) ? (x_) : (0);
    this.y = (y_ >= 0) ? (y_) : (0);
    this.owner = owner_;
    this.king = false;
  }
  public void move() {
    
  }
}