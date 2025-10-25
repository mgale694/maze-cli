#ifndef RUNNER_H
#define RUNNER_H

#include "builder.h"

class GameRunner {
private:
  Maze& maze;
  int playerRow;
  int playerCol;
  int startRow;
  int startCol;
  int endRow;
  int endCol;
  
  void displayMaze() const;
  bool isValidMove(int row, int col) const;
  bool hasWon() const;
  char getUserMove();
  void movePlayer(char direction);

public:
  GameRunner(Maze& m);
  void start();
};

#endif // RUNNER_H
