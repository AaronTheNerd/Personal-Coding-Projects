// Written by Aaron Barge
// Copyright 2019

#ifndef _TICTACTOE_TICTACTOE_H_
#define _TICTACTOE_TICTACTOE_H_

#include <string>
#include <vector>
namespace game {
  using pos = std::pair<int, int>;
  static const bool BOT_FIRST = true;
class tictactoe {
 public:
  tictactoe();
  tictactoe(bool);
 private:
  const int BOT_SPACE = 1;
  const int USER_SPACE = 0;
  const int FREE_SPACE = -1;
  int turn;
  pos last_move;
  pos bot_last_move;
  int board[3][3];
  void init_board();
  void play();
  void bot_play();
  void user_play();
  bool game_over() const;
  bool cat_game() const;
  void print_board() const;
  std::string space(int, int) const;
  bool can_win(int, pos, pos&) const;
  bool bot_can_fork(pos&) const;
  bool can_fork(int, int, int) const;
  bool bot_can_block_user_fork(pos&) const;
  bool block_all_forks_and_defend(std::vector<pos>, pos) const;
  pos block_without_fork(std::vector<pos>) const;
  bool user_played_corner(pos&) const;
  bool has_empty_corner(pos&) const;
  void bot_play_side();
};
} // End namespace game

#endif