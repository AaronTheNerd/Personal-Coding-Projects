public class Checkers {
  Board checker_board;
  Player current_player;

  Checkers (Player p_1, Player p_2) {
    checker_board = new Board(p_1, p_2);
    current_player = checker_board.player_1;
  }
  void show() {
    
  }
  void changePlayers() {
    current_player = current_player.equals(checker_board.player_1) ? 
    checker_board.player_2 : 
    checker_board.player_1;
  }
  boolean checkForMoves(Piece p) {

  }
  boolean checkForJump(Piece p) {

  }
  void move() {

  }
}