#include "../include/builder.h"
#include <iostream>

std::vector<std::vector<char>> createGrid(int width, int height) {
  std::vector<std::vector<char>> grid(height, std::vector<char>(width, '#'));
  return grid;
}

void debugPrintGrid(const std::vector<std::vector<char>> &grid) {
  for (const auto &row : grid) {
    for (char cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}

void buildMaze() {
  int width, height;
  
  std::cout << "Enter maze width: ";
  std::cin >> width;
  
  std::cout << "Enter maze height: ";
  std::cin >> height;
  
  // Implementation for building a maze
  // 1. Create grid
  auto grid = createGrid(width, height);
  debugPrintGrid(grid);
  // 2. Place start and end points
  // 3. Add correct Implementation path
  // 4. Randomly fill remaining namespace
}
