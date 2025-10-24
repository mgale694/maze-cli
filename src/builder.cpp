#include "../include/builder.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

/*
 * Function to get user input for maze dimensions
 *
 * @param width Reference to the width variable
 * @param height Reference to the height variable
 */
void userInputDimensions(int &width, int &height) {
  std::string input;

  std::cout << "Enter maze width (default " << width << "): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    std::stringstream ss(input);
    ss >> width;
  }

  std::cout << "Enter maze height (default " << height << "): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    std::stringstream ss(input);
    ss >> height;
  }
}

/*
 * Function to create a grid initialized with walls ('#')
 *
 * @param width The width of the grid
 * @param height The height of the grid
 *
 * @return A 2D vector representing the grid
 */
std::vector<std::vector<char>> createGrid(int width, int height) {
  std::vector<std::vector<char>> grid(height, std::vector<char>(width, '#'));
  return grid;
}

int pickStartOrEnd(int height) {
  int position = rand() % height;
  return position;
}

void debugPrintGrid(const std::vector<std::vector<char>> &grid) {
  for (const auto &row : grid) {
    for (char cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}

void updateGridWithStartEnd(std::vector<std::vector<char>> &grid, int start,
                            int end) {
  grid[start][0] = ' ';                // Start point
  grid[end][grid[0].size() - 1] = ' '; // End point
}

void createCorrectPath(std::vector<std::vector<char>> &grid, int startRow,
                       int startCol, int endRow, int endCol) {
  int currentRow = startRow;
  int currentCol = startCol;

  // Mark starting position
  grid[currentRow][currentCol] = ' ';

  int horizontalMoveCount = 0;

  // Alternate between horizontal and vertical moves
  while (currentRow != endRow || currentCol != endCol) {
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

    // Move horizontally if needed (and we didn't just force a vertical move)
    if (!forcedVertical && currentCol != endCol) {
      horizontalMoveCount++;
      if (currentCol < endCol) {
        currentCol++;
      } else {
        currentCol--;
      }
      grid[currentRow][currentCol] = ' ';
    }
    // Move vertically if needed (and we haven't already)
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

void fillRandomPaths(std::vector<std::vector<char>> &grid, int percentage) {
  int height = grid.size();
  int width = grid[0].size();

  // Go through each cell in the grid
  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      // Only modify cells that are currently walls
      if (grid[row][col] == '#') {
        // Randomly decide to carve this cell based on percentage
        if ((rand() % 100) < percentage) {
          grid[row][col] = ' ';
        }
      }
    }
  }
}

void buildMaze() {
  int width = 75, height = 20;

  std::cout << "Building a new maze!\n";

  // 0. Get user input for dimensions (default 50x25)
  userInputDimensions(width, height);

  // Seed random number generator
  srand(time(0));

  // Implementation for building a maze
  // 1. Create grid
  auto grid = createGrid(width, height);
  // 2. Place start and end points
  int start = pickStartOrEnd(height);
  int end = pickStartOrEnd(height);
  updateGridWithStartEnd(grid, start, end);
  // 3. Add correct path
  createCorrectPath(grid, start, 0, end, width - 1);
  // 4. Fill random paths (20% of remaining walls become paths)
  fillRandomPaths(grid, 50);
  debugPrintGrid(grid);
}
