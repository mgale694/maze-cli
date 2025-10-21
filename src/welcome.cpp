#include "../include/welcome.h"
#include <iostream>

void printWelcome() { std::cout << "Welcome to the Maze Game!" << std::endl; }

void explainRules() {
  std::cout << "Rules: Navigate through the maze to reach the end point."
            << "\n";

  std::cout << "Use the arrow keys to move, or the h,j,k,l as with vim."
            << "\n";
  std::cout << "Good luck!" << std::endl;
}

void welcomeMessage() {
  printWelcome();
  explainRules();
}
