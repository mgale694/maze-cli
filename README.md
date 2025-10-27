# Maze CLI Game

A command-line maze game written in C++ where you navigate through a randomly generated maze from the left edge to the right edge.

## Features

- **Random Maze Generation**: Generates unique mazes with a guaranteed solution path
- **Customizable Size**: User can specify maze width and height (default: 75x20)
- **ASCII Display**: Uses `#` for walls, spaces for paths, and `*` for player position
- **Vim-style Controls**: Navigate using h (left), j (down), k (up), l (right)
- **Interactive Gameplay**: Real-time maze display updates after each move
- **Win Detection**: Celebrates when you reach the exit

## Building the Project

This project uses CMake for building:

```bash
# Create build directory
mkdir -p build
cd build

# Configure and build
cmake ..
make

# Run the game
./MazeCLI
```

### Requirements

- CMake 3.23 or higher
- C++20 compatible compiler (g++, clang++)
- GLFW3 (included in dependencies)

## How to Play

1. Run the executable
2. Enter desired maze dimensions (or press Enter for defaults)
3. Navigate from the start position (left edge) to the exit (right edge)
4. Use keyboard controls:
   - `h` - Move left
   - `j` - Move down
   - `k` - Move up
   - `l` - Move right
   - `q` - Quit game

## Project Structure

```
maze-cli/
├── main.cpp              # Entry point and user input handling
├── CMakeLists.txt        # Build configuration
├── include/
│   ├── builder.h         # Maze class declaration
│   ├── runner.h          # GameRunner class declaration
│   └── welcome.h         # Welcome message functions
└── src/
    ├── builder.cpp       # Maze generation implementation
    ├── runner.cpp        # Game loop and player movement
    └── welcome.cpp       # Welcome and rules display
```

## Architecture

### Maze Class (`builder.h/cpp`)

- Generates maze grid with walls and paths
- Places random start and end positions on left/right edges
- Creates a guaranteed solution path
- Fills remaining space with random paths (50% density)

### GameRunner Class (`runner.h/cpp`)

- Manages game state and player position
- Handles movement validation and collision detection
- Updates and displays the maze after each move
- Checks win condition

### Main Flow

1. Display welcome message and rules
2. Prompt user for maze dimensions
3. Generate maze using `Maze` class
4. Start game loop with `GameRunner`
5. Process player input and update display
6. Detect win condition and celebrate

## Implementation Details

- **Maze Generation Algorithm**: Creates a simple path from start to end using horizontal and vertical moves, with forced vertical movement every 3 horizontal steps to prevent straight lines
- **Random Fill**: Fills 50% of remaining walls with paths for visual complexity
- **OOP Design**: Uses classes for clean separation of concerns (Maze generation vs. Game logic)
- **Standard Library**: Relies primarily on C++ standard library (vector, iostream, etc.)
