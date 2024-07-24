#include "game.hpp"
#include <iostream>

using namespace std;

int main() {
  string a, b;

  // Display intro text and collect the names of the players
  cout << "This is a 2 player best of 3 Tic-Tac-Toe game \n\n";
  cout << "Enter the name of player one: "; 
  cin >> a;
  cout << "\nEnter the name of player two: "; 
  cin >> b;
  cout << "\n";

  // create game
  Game g1 = Game(a, b);

  // game loop
  string win = g1.gm_loop();
  cout << "\n\n  GAME OVER  \n  The winner is " << win << ".\n";
}
