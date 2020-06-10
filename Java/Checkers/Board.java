import java.util.ArrayList;
import java.awt.Color;
public class Board {
  public static final int BOARD_SIZE = 8;
  public static final Color BOARD_COLOR_1 = Color.RED;
  public static final Color BOARD_COLOR_2 = Color.BLACK;
  Player player_1;
  Player player_2;
  Player current_player;
  Piece[][] board = new Piece[BOARD_SIZE][BOARD_SIZE];

  Board(Player p_1, Player p_2) {
    player_1 = p_1;
    player_2 = p_2;
    current_player = player_1;
    init();
  }
  void init() {
    makeBoard();
    if (player_1.side == player_2.side)
      player_2.side = !player_1.side;
    placePieces();
  }
  void makeBoard() {
    for (int y = 0; y < BOARD_SIZE; ++y)
      for (int x = 0; x < BOARD_SIZE; ++x)
        this.board[x][y] = null;
  }
  void placePieces() {
    placeTopPieces();
    placeBottomPieces();
  }
  void placeTopPieces() {
    for (int y = 0; y < BOARD_SIZE / 2 - 1; ++y) {
      for (int x = 0; x < BOARD_SIZE; ++x) {
        if ((y * BOARD_SIZE + x) % 2 == y % 2) {
          if (player_1.side == Player.TOP) {
            board[x][y] = new Piece(x, y, player_1);
          } else {
            board[x][y] = new Piece(x, y, player_2);
          }
        }
      }
    }
  }
  void placeBottomPieces() {
    for (int y = BOARD_SIZE / 2 + 1; y < BOARD_SIZE; ++y) {
      for (int x = 0; x < BOARD_SIZE; ++x) {
        if ((y * BOARD_SIZE + x) % 2 == y % 2) {
          if (player_1.side != Player.TOP) {
            board[x][y] = new Piece(x, y, player_1);
          } else {
            board[x][y] = new Piece(x, y, player_2);
          }
        }
      }
    }
  }
  void changePlayers() {
    current_player = current_player.equals(player_1) ? 
    player_2 : 
    player_1;
  }
  boolean checkForMoves(Piece p) {
    
  }
  boolean checkForJump(Piece p) {

  }
  void move() {

  }
}