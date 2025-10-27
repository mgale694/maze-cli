#include "include/builder.h"
#include "include/runner.h"
#include "include/welcome.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
// welcomeMessage function
// printWelcome
// explainRules
//
// buildMaze function
// userInputSize
// gernerateMaze
//
// gernateMaze function
// createGrid
// placeStartEnd
// addCorrectPath
// randomFill
//
// startGame function
// loop...
// displayMaze
// getUserMove
// checkMoveValidity
// updatePlayerPosition
// checkWinCondition
// exit loop...
// displayMaze
//
// endGame function
// displayWinMessage

int main() {
  welcomeMessage();

  // Get user input for dimensions
  int width = 75, height = 20;
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

  // Initialize and generate maze
  Maze maze(width, height);
  maze.generate();
  maze.debugPrint();

  // Start the game
  GameRunner game(maze);
  game.start();

  return 0;
}
