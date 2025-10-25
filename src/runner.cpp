#include "../include/runner.h"
#include <iostream>

GameRunner::GameRunner(Maze& m) : maze(m), playerRow(0), playerCol(0), 
                                   startRow(0), startCol(0), endRow(0), endCol(0) {
  // Find start and end positions in the maze
  const auto& grid = maze.getGrid();
  int height = grid.size();
  int width = grid[0].size();
  
  // Find start position (left edge)
  for (int row = 0; row < height; row++) {
    if (grid[row][0] == ' ') {
      startRow = row;
      startCol = 0;
      playerRow = row;
      playerCol = 0;
      break;
    }
  }
  
  // Find end position (right edge)
  for (int row = 0; row < height; row++) {
    if (grid[row][width - 1] == ' ') {
      endRow = row;
      endCol = width - 1;
      break;
    }
  }
}

void GameRunner::displayMaze() const {
  const auto& grid = maze.getGrid();
  
  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      if (row == playerRow && col == playerCol) {
        std::cout << '*';
      } else {
        std::cout << grid[row][col];
      }
    }
    std::cout << std::endl;
  }
}

bool GameRunner::isValidMove(int row, int col) const {
  const auto& grid = maze.getGrid();
  
  // Check bounds
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
    return false;
  }
  
  // Check if it's a wall
  if (grid[row][col] == '#') {
    return false;
  }
  
  return true;
}

bool GameRunner::hasWon() const {
  return playerRow == endRow && playerCol == endCol;
}

char GameRunner::getUserMove() {
  std::cout << "\nUse h (left), j (down), k (up), l (right) to move, or q to quit: ";
  char move;
  std::cin >> move;
  return move;
}

void GameRunner::movePlayer(char direction) {
  int newRow = playerRow;
  int newCol = playerCol;
  
  switch(direction) {
    case 'h': // left
      newCol--;
      break;
    case 'j': // down
      newRow++;
      break;
    case 'k': // up
      newRow--;
      break;
    case 'l': // right
      newCol++;
      break;
    default:
      std::cout << "Invalid move! Use h, j, k, or l." << std::endl;
      return;
  }
  
  if (isValidMove(newRow, newCol)) {
    playerRow = newRow;
    playerCol = newCol;
  } else {
    std::cout << "Can't move there! Hit a wall." << std::endl;
  }
}

void GameRunner::start() {
  std::cout << "\n=== Maze Game Started ===" << std::endl;
  std::cout << "Navigate from the left edge to the right edge!" << std::endl;
  std::cout << "Controls: h=left, j=down, k=up, l=right, q=quit" << std::endl;
  
  while (!hasWon()) {
    std::cout << "\n";
    displayMaze();
    
    char move = getUserMove();
    
    if (move == 'q') {
      std::cout << "Thanks for playing!" << std::endl;
      return;
    }
    
    movePlayer(move);
  }
  
  std::cout << "\n";
  displayMaze();
  std::cout << "\n🎉 Congratulations! You won! 🎉" << std::endl;
}
