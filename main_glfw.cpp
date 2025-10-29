#include "include/builder.h"
#include "include/graphical_maze.h"
#include "include/welcome.h"
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    welcomeMessage();

    // Get user input for dimensions
    int width = 50, height = 30;
    std::string input;

    std::cout << "\nEnter maze width (default " << width << "): ";
    std::getline(std::cin, input);
    if (!input.empty())
    {
        std::stringstream ss(input);
        ss >> width;
    }

    std::cout << "Enter maze height (default " << height << "): ";
    std::getline(std::cin, input);
    if (!input.empty())
    {
        std::stringstream ss(input);
        ss >> height;
    }

    // Validate dimensions
    if (width < 10 || width > 200 || height < 10 || height > 100)
    {
        std::cerr << "Invalid dimensions! Width must be 10-200, height must be 10-100." << std::endl;
        return 1;
    }

    std::cout << "\nGenerating " << width << "x" << height << " maze..." << std::endl;

    // Initialize and generate maze
    Maze maze(width, height);
    maze.generate();

    // Create and initialize graphical game
    GraphicalMaze game(maze);

    if (!game.initialize())
    {
        std::cerr << "Failed to initialize graphical maze game!" << std::endl;
        return 1;
    }

    // Run the game
    game.run();

    return 0;
}
