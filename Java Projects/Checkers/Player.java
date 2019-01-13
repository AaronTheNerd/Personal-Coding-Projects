import java.util.ArrayList;
import java.awt.Color;
public class Player {
  public static final boolean TOP = true;
  String name;
  Color piece_color;
  boolean side;
  Player(String aName) {
    name = (!aName.equals("")) ? aName : RandomName.Generate();
    side = Player.TOP;
    piece_color = Color.GRAY;
  }
  void setColor(Color aColor) {
    piece_color = aColor;
  }
}