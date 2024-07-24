// player.hpp
#pragma once

#include <string>

using namespace std;

class Player {
  string name;
  int score;
  int indx;

public:

  Player(string n, int i) : name(n), score(0), indx(i){}
  
  void p_win() {
    score++;
  }

  int get_score() {
    return score;
  }
  
  string get_name() {
    return name;
  }

  int get_index() {
    return indx;
  }
};
