import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.*;
public class Checkers {
  private int height;
  private int width;

  Board checker_board;

  Checkers (Player p_1, Player p_2) {
    JFrame main_frame = new JFrame("Checkers");

    CheckerPanel board_panel = new CheckerPanel();
    board_panel.addMouseMotionListener(new MouseAdapter() {
      @Override
      public void mouseClicked(MouseEvent e) {
        // TODO Show possible spaces for a piece
        Piece p = findPiece(e.getX(), e.getY());
      }
      @Override
      public void mouseDragged(MouseEvent e) {
        Piece p = findPiece(e.getX(), e.getY());
      }
    });
    checker_board = new Board(p_1, p_2);
  }
  void show() {
    drawBoard();
    showPieces(checker_board.player_1);
    showPieces(checker_board.player_2);
  }
  void drawBoard() {
    Color current_color = Board.BOARD_COLOR_1;

  }
  void showPieces(Player p) {

  }
  Piece findPiece(int x, int y) {
    int boardX = (int) Math.floor((Board.BOARD_SIZE * x) / width);
    int boardY = (int) Math.floor((Board.BOARD_SIZE * y) / height);
    return checker_board.board[boardX][boardY];
  }
}
class CheckerPanel extends JPanel {
  // Forces the panel to be a square shape
  @Override
  public Dimension getPreferredSize() {
    Dimension d = super.getPreferredSize();
    Container c = getParent();
    if (c != null) {
      d = c.getSize();
    } else {
      return new Dimension(10, 10);
    }
    int w = (int) d.getWidth();
    int h = (int) d.getHeight();
    int s = (w < h ? w : h);
    return new Dimension(s, s);
    }
}