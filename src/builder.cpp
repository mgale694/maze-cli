#include "../include/builder.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Maze::Maze(int w, int h) : width(w), height(h), startRow(0), endRow(0) {
  srand(time(0));
}

void Maze::createGrid() {
  grid = std::vector<std::vector<char>>(height, std::vector<char>(width, '#'));
}

int Maze::pickRandomRow() { return rand() % height; }

void Maze::placeStartEnd() {
  startRow = pickRandomRow();
  endRow = pickRandomRow();
  grid[startRow][0] = ' ';
  grid[endRow][width - 1] = ' ';
}

void Maze::createCorrectPath() {
  int currentRow = startRow;
  int currentCol = 0;

  grid[currentRow][currentCol] = ' ';

  int horizontalMoveCount = 0;

  while (currentRow != endRow || currentCol != width - 1) {
    bool forcedVertical = false;

    // Force a vertical move if we've moved horizontally too long
    if (horizontalMoveCount >= 3 && currentRow != endRow) {
      horizontalMoveCount = 0;
      if (currentRow < endRow) {
        currentRow++;
      } else {
        currentRow--;
      }
      grid[currentRow][currentCol] = ' ';
      forcedVertical = true;
    }

    // Move horizontally if needed
    if (!forcedVertical && currentCol != width - 1) {
      horizontalMoveCount++;
      currentCol++;
      grid[currentRow][currentCol] = ' ';
    }
    // Move vertically if needed
    else if (!forcedVertical && currentRow != endRow) {
      horizontalMoveCount = 0;
      if (currentRow < endRow) {
        currentRow++;
      } else {
        currentRow--;
      }
      grid[currentRow][currentCol] = ' ';
    }
  }
}

void Maze::fillRandomPaths(int percentage) {
  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      if (grid[row][col] == '#') {
        if ((rand() % 100) < percentage) {
          grid[row][col] = ' ';
        }
      }
    }
  }
}

void Maze::generate() {
  createGrid();
  placeStartEnd();
  createCorrectPath();
  fillRandomPaths(50);
}

void Maze::debugPrint() const {
  for (const auto &row : grid) {
    for (char cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}

const std::vector<std::vector<char>> &Maze::getGrid() const { return grid; }
