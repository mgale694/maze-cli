#include "../include/builder.h"
#include <iostream>
#include <sstream>
#include <string>

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

void debugPrintGrid(const std::vector<std::vector<char>> &grid) {
  for (const auto &row : grid) {
    for (char cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}

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

void buildMaze() {
  int width = 50, height = 25;

  std::cout << "Building a new maze!\n";

  // 0. Get user input for dimensions (default 50x25)
  userInputDimensions(width, height);

  // Implementation for building a maze
  // 1. Create grid
  auto grid = createGrid(width, height);
  debugPrintGrid(grid);
  // 2. Place start and end points
  // 3. Add correct Implementation path
  // 4. Randomly fill remaining namespace
}
