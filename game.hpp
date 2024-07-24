// game.hpp
#pragma once

#include "player.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game {
  vector<vector<int>> board;
  Player *a;
  Player *b;
  Player *cur_player;
  int no_moves;

public:
  Game(string pa, string pb)
      : a(new Player(pa, 1)), b(new Player(pb, 2)), cur_player(a) {
    no_moves = 0;
    // populate the board;
    for (int i = 0; i < 3; i++) {
      board.push_back({});
      for (int j = 0; j < 3; j++) {
        board[i].push_back(0);
      }
    }
  }

  ~Game() {
    delete a;
    delete b;
  }

  string gm_loop() {
    string winner_name;
    while (a->get_score() < 3 && b->get_score() < 3) {
      draw_board();

      if(no_moves == 9) {
        cout << "\nTHIS GAME IS A DRAW !!!!!!!!!\n\n\n\n NEW GAME\n";
        gm_reset();
        continue;
      }

      cout << "\ncurrent player is :" << cur_player->get_name() << "\n";
      get_inp();

      if (winner()) {
        cur_player->p_win();
        draw_board();
        if(cur_player->get_score() < 3) {
          cout << cur_player->get_name() << " WINS!!!!!!!\n\n\n\n NEW GAME\n";
        } else {
          cout << cur_player->get_name() << " WINS!!!!!!!";
        }
        winner_name = cur_player->get_name();
        gm_reset();
        continue;
      }

      change_cur_player();
      no_moves++;
    }

    return winner_name;
  }

  void get_inp() {
    int row, col;
    cout << "\n enter the row value of player " << cur_player->get_index()
         << " for the next move (betweeen 0 and 2): ";
    cin >> row;
    cout << "\n enter the col value of player " << cur_player->get_index()
         << " for the next move (between 0 and 2): ";
    cin >> col;
    cout << "\n";

    while (!eval_inp(row, col)) {
      cout << "\n!! INCOMPATIBLE INPUT !!";
      cout << "\n enter the row value of player " << cur_player->get_index()
           << " for the next move (betweeen 0 and 2): ";
      cin >> row;
      cout << "\n enter the col value of player " << cur_player->get_index()
           << " for the next move (between 0 and 2): ";
      cin >> col;
      cout << "\n";
    }

    inp(row, col, cur_player->get_index());
  }

  void gm_reset() {
    no_moves = 0;
    cur_player = a;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = 0;
      }
    }
  }

  void change_cur_player() {
    if (cur_player == a) {
      cur_player = b;
    } else {
      cur_player = a;
    }
  }

  bool eval_inp(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == 0) {
      return true;
    } else {
      return false;
    }
  }

  // returns winning player number or 0;
  bool winner() {
    int col, row;
    int count, start;

    // check rows for winner
    for (row = 0; row < 3; row++) {
      start = board[row][0];
      if (start == 0)
        continue;
      count = 1;
      for (col = 1; col < 3; col++) {
        if (board[row][col] != start) {
          break;
        }
        count++;
      }
      if (count == 3) {
        return true;
      }
    }

    // check columns for winner
    for (col = 0; col < 3; col++) {
      start = board[0][col];
      if (start == 0)
        continue;
      count = 1;
      for (row = 1; row < 3; row++) {
        if (board[row][col] != start) {
          break;
        }
        count++;
      }
      if (count == 3) {
        return true;
      }
    }

    // check positive diagonal for the winners
    start = board[0][0];
    if (start != 0 && board[1][1] == start && board[2][2] == start) {
      return true;
    }

    // check negative diagonal for the winners
    start = board[2][0];
    if (start != 0 && board[1][1] == start && board[0][2] == start) {
      return true;
    }

    return false;
  }

  void draw_board() {
    cout << "    Tic-Tac-Toe(Best of 3)" << "\n\n";
    cout << "Player 1 : " << a->get_name()
         << "    symbol: x    score: " << a->get_score() << "\n";

    cout << "Player 2 : " << b->get_name()
         << "    symbol: 0    score: " << b->get_score() << "\n\n";

    cout << "Board: ";
    for (int row = 0; row < 3; row++) {
      cout << "\t\t\t\t";
      for (int col = 0; col < 3; col++) {
        switch (board[row][col]) {
        case 1:
          cout << "x" << " ";
          break;
        case 2:
          cout << "O" << " ";
          break;
        default:
          cout << "_ ";
        }
      }
      cout << "\n";

    }

  }

  void inp(int row, int col, int pl) {
    board[row][col] = cur_player->get_index();
  }
};
