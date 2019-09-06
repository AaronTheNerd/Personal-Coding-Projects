// Written by Aaron Barge
// Copyright 2019

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "tictactoe.h"
using namespace game;



// ========================================================================================================================= //
//                                                      Initialization
// ========================================================================================================================= //
tictactoe::tictactoe() {
  this->print_board();
}

tictactoe::tictactoe(bool bot_first) {
  turn = 0;
  this->init_board();
  if (bot_first) {
    this->bot_play();
  }
  this->play();
}

void tictactoe::init_board() {
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      this->board[x][y] = FREE_SPACE;
    }
  }
  last_move = pos(0, 0);
  bot_last_move = pos(0, 0);
}



// ========================================================================================================================= //
//                                                        User Play
// ========================================================================================================================= //
void tictactoe::play() {
  while (!this->game_over() && !this->cat_game()) {
    this->user_play();
    if (this->game_over() || this->cat_game())
      break;
    this->bot_play();
  }
  this->print_board();
  std::cout << "Game Over!" << std::endl;
}

void tictactoe::user_play() {
  this->print_board();
  int user_choice = -1;
  while (user_choice < 1 || user_choice > 9) {
    std::cout << "Your move" << std::endl;
    std::cin.clear();
    std::cin >> user_choice;
    if (!std::cin) {
      user_choice = -1;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    }
    if (this->board[(user_choice - 1) / 3][(user_choice - 1) % 3] != FREE_SPACE) {
      user_choice = -1;
    }
  }
  user_choice--;
  last_move = pos(user_choice / 3, user_choice % 3);
  this->board[last_move.first][last_move.second] = USER_SPACE;
  turn++;
}



// ========================================================================================================================= //
//                                                        End Game
// ========================================================================================================================= //
bool tictactoe::game_over() const {
  for (int i = 0; i < 3; ++i) {
    if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != FREE_SPACE)
        || (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != FREE_SPACE)) {
      return true;
    }
  }
  if (((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
      || (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]))
      && this->board[1][1] != FREE_SPACE) {
    return true;
  }
  return false;
}

bool tictactoe::cat_game() const {
  return turn == 9;
}



// ========================================================================================================================= //
//                                                       Print Method
// ========================================================================================================================= //
void tictactoe::print_board() const {
  for (int y = 0; y < 3; ++y) {
    std::cout << "   |   |   " << std::endl;
    std::cout << this->space(y,0) << "|" << this->space(y,1) << "|" << this->space(y,2) << std::endl;
    std::cout << "   |   |   " << std::endl;
    if (y != 2)
      std::cout << "---+---+---" << std::endl;
  }
}

std::string tictactoe::space(int x, int y) const {
  int pos_ = x*3 + y + 1;
  std::stringstream ss;
  ss << pos_;
  return this->board[x][y] == USER_SPACE ? " X " : this->board[x][y] == BOT_SPACE ? " O " : " " + ss.str() + " ";
}



// ========================================================================================================================= //
//                                                        Bot Play
// ========================================================================================================================= //
void tictactoe::bot_play() {
  pos p(-1, -1);
  if (this->can_win(BOT_SPACE, bot_last_move, p)) { // Win
    std::cout << "Bot can win" << std::endl;
    this->board[p.first][p.second] = BOT_SPACE;
  } else if (this->can_win(USER_SPACE, last_move, p)) { // Block
    std::cout << "User can win" << std::endl;
    this->board[p.first][p.second] = BOT_SPACE;
  } else if (this->bot_can_fork(p)) { // Fork
    this->board[p.first][p.second] = BOT_SPACE;
  } else if (this->bot_can_block_user_fork(p)) { // Block Fork
    this->board[p.first][p.second] = BOT_SPACE;
  } else if (this->board[1][1] == FREE_SPACE) { // Center
    this->board[1][1] = BOT_SPACE;
  } else if (this->user_played_corner(p)) { // Opposite Corner
    this->board[p.first][p.second] = BOT_SPACE;
  } else if (this->has_empty_corner(p)) { // Empty Corner
    this->board[p.first][p.second] = BOT_SPACE;
  } else { // Empty Side
    this->bot_play_side();
  }
  bot_last_move = p;
  turn++;
}

bool tictactoe::can_win(int space, pos last_move_, pos& p) const {
  int h_space = 0, h_free = 0, v_space = 0, v_free = 0, d_space_1 = 0, d_free_1 = 0, d_space_2 = 0, d_free_2 = 0;
  pos h_pos, v_pos, d_pos_1, d_pos_2;
  for (int i = 0; i < 3; ++i) {
    if (this->board[i][last_move_.second] == space) {
      v_space++;
    } else if (this->board[i][last_move_.second] == FREE_SPACE) {
      v_free++;
      v_pos = pos(i, last_move_.second);
    }
    if (this->board[last_move_.first][i] == space) {
      h_space++;
    } else if (this->board[last_move_.first][i] == FREE_SPACE) {
      h_free++;
      h_pos = pos(last_move_.first, i);
    }
    if (this->board[i][i] == space) {
      d_space_1++;
    } else if (this->board[i][i] == FREE_SPACE) {
      d_free_1++;
      d_pos_1 = pos(i, i);
    }
    if (this->board[i][2 - i] == space) {
      d_space_2++;
    } else if (this->board[i][2 - i] == FREE_SPACE) {
      d_free_2++;
      d_pos_2 = pos(i, 2 - i);
    }
  }
  if (h_space == 2 && h_free == 1) {
    p = h_pos;
    return true;
  }
  if (v_space == 2 && v_free == 1) {
    p = v_pos;
    return true;
  }
  if (d_space_1 == 2 && d_free_1 == 1) {
    p = d_pos_1;
    return true;
  }
  if (d_space_2 == 2 && d_free_2 == 1) {
    p = d_pos_2;
    return true;
  }
  return false;
}

bool tictactoe::bot_can_fork(pos& p) const {
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      if (this->board[x][y] == FREE_SPACE) {
        if (this->can_fork(BOT_SPACE, x, y)) {
          p = pos(x, y);
          return true;
        }
      }
    }
  }
  return false;
}

bool tictactoe::can_fork(int space, int x, int y) const {
  int h_space = 0, h_free = 0, v_space = 0, v_free = 0, d_space_1 = 0, d_free_1 = 0, d_space_2 = 0, d_free_2 = 0;
  bool check_d1 = x == y;
  bool check_d2 = y == 2 - x;
  for (int i = 0; i < 3; ++i) {
    if (this->board[i][y] == space) {
      v_space++;
    } else if (this->board[i][y] == FREE_SPACE) {
      v_free++;
    }
    if (this->board[x][i] == space) {
      h_space++;
    } else if (this->board[x][i] == FREE_SPACE) {
      h_free++;
    }
    if (this->board[i][i] == space) {
      d_space_1++;
    } else if (this->board[i][i] == FREE_SPACE) {
      d_free_1++;
    }
    if (this->board[i][2 - i] == space) {
      d_space_2++;
    } else if (this->board[i][2 - i] == FREE_SPACE) {
      d_free_2++;
    }
  }
  if (h_space == 1 && h_free == 2) {
    return true;
  }
  if (v_space == 1 && v_free == 2) {
    return true;
  }
  if (d_space_1 == 1 && d_free_1 == 2 && check_d1) {
    return true;
  }
  if (d_space_2 == 1 && d_free_2 == 2 && check_d2) {
    return true;
  }
  return false;
}

bool tictactoe::bot_can_block_user_fork(pos& p) const {
  /*
    If there is only one possible fork for the opponent, the player should block it.
    Otherwise, the player should block all forks in any way that simultaneously allows them to create two in a row.
    Otherwise, the player should create a two in a row to force the opponent into defending, as long as it doesn't result in them creating a fork.
    For example, if "X" has two opposite corners and "O" has the center, "O" must not play a corner in order to win.
    (Playing a corner in this scenario creates a fork for "X" to win.)
  */
  std::vector<pos> forks;
  for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y)
      if (this->board[x][y] == FREE_SPACE)
        if (this->can_fork(USER_SPACE, x, y))
          forks.push_back(pos(x, y));
  pos p_;
  if (forks.size() == 0)
    return false;
  if (forks.size() == 1) {
    p = forks[0];
    return true;
  } else if (this->block_all_forks_and_defend(forks, p_)) {
    p = p_;
    return true;
  } else {
    p = this->block_without_fork(forks);
    return true;
  }
  return false;
}

bool tictactoe::block_all_forks_and_defend(std::vector<pos> forks, pos p) const {
  p = forks[forks.size() - 1];
  return true;
}

pos tictactoe::block_without_fork(std::vector<pos> forks) const {
  return forks[0];
}

bool tictactoe::user_played_corner(pos& p) const {
  if (this->last_move == pos(0, 0) && this->board[2][2] == FREE_SPACE) {
    p = pos(2, 2);
    return true;
  } else if (this->last_move == pos(2, 2) && this->board[0][0] == FREE_SPACE) {
    p = pos(0, 0);
    return true;
  } else if (this->last_move == pos(0, 2) && this->board[2][0] == FREE_SPACE) {
    p = pos(2, 0);
    return true;
  } else if (this->last_move == pos(2, 0) && this->board[0][2] == FREE_SPACE) {
    p = pos(0, 2);
    return true;
  }
  return false;
}

bool tictactoe::has_empty_corner(pos& p) const {
  if (this->board[0][0] == FREE_SPACE) {  
    p = pos(0, 0);
    return true;
  } else if (this->board[2][2] == FREE_SPACE) {
    p = pos(2, 2);
    return true;
  } else if (this->board[0][2] == FREE_SPACE) {
    p = pos(0, 2);
    return true;
  } else if (this->board[2][0] == FREE_SPACE) {
    p = pos(2, 0);
    return true;
  }
  return false;
}

void tictactoe::bot_play_side() {
  if (this->board[1][0] == FREE_SPACE)
    this->board[1][0] = BOT_SPACE;
  else if (this->board[0][1] == FREE_SPACE)
    this->board[0][1] = BOT_SPACE;
  else if (this->board[1][2] == FREE_SPACE)
    this->board[1][2] = BOT_SPACE;
  else
    this->board[2][1] = BOT_SPACE;
}