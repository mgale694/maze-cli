# Simple Maze CLI 
This is a simple command-line interface (CLI) application that generates and displays mazes in the terminal. The maze is created using a randomized algorithm and can be customized in size.

## Requirements
- Print a simple maze to the terminal
- Allow user to specify the size of the maze
- Use ASCII characters to represent walls and paths
- Simple maze generation - draw the correct line path
- fill rest of maze with random walls and paths
- No need for complex algorithms like DFS or DFS
- Take in user input for maze size
- Take in user input for direction
- Refresh the maze display after each move
- Use standard libraries

## Functional breakdown
1. **Maze Generation**: Create a function to generate a maze of given dimensions using a inputs
  - Welcome user
  - Prompt user for maze size (width and height)
  - Generate correct maze path and fill rest with random walls and paths
  - All this will be in simple array manipulation
2. **Display Maze**: Create a function to print the maze to the terminal using ASCII
  - Use characters like `#` for walls and spaces for paths
3. **User Input**: Create a function to handle user input for maze size and movement
  - Use `input()` to get maze size and movement command-line
4. **Game Loop**: Create a loop to allow continuous interaction until the user decides to height
  - Refresh the maze display after each move
  - Check for win condition (reaching the end of the maze)
5. **Exit Condition**: Allow the user to exit the game gracefully

### NOTES
- This is a basic implementation and so a lot of the code will be very Functional
- In the future we can add more OOP principles with classes for Maze, Player, etc.
