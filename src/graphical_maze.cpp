#include "../include/graphical_maze.h"
#include <iostream>
#include <cmath>

// Static callback implementations
void GraphicalMaze::errorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GraphicalMaze::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    // Get the GraphicalMaze instance from user pointer
    GraphicalMaze *game = static_cast<GraphicalMaze *>(glfwGetWindowUserPointer(window));
    if (!game)
        return;

    // Don't process input if game is won
    if (game->gameWon)
    {
        if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        return;
    }

    int newRow = game->playerRow;
    int newCol = game->playerCol;
    bool moved = false;

    switch (key)
    {
    case GLFW_KEY_LEFT:
    case GLFW_KEY_H:
        newCol--;
        moved = true;
        break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_L:
        newCol++;
        moved = true;
        break;
    case GLFW_KEY_UP:
    case GLFW_KEY_K:
        newRow--;
        moved = true;
        break;
    case GLFW_KEY_DOWN:
    case GLFW_KEY_J:
        newRow++;
        moved = true;
        break;
    case GLFW_KEY_ESCAPE:
    case GLFW_KEY_Q:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    if (moved && game->isValidMove(newRow, newCol))
    {
        game->playerRow = newRow;
        game->playerCol = newCol;

        // Check win condition
        if (game->playerRow == game->endRow && game->playerCol == game->endCol)
        {
            game->gameWon = true;
            std::cout << "🎉 Congratulations! You won! 🎉" << std::endl;
        }
    }
}

// Constructor
GraphicalMaze::GraphicalMaze(Maze &m)
    : maze(m), window(nullptr), playerRow(0), playerCol(0),
      startRow(0), startCol(0), endRow(0), endCol(0),
      mazeWidth(0), mazeHeight(0), gameWon(false)
{
}

// Destructor
GraphicalMaze::~GraphicalMaze()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// Find start and end positions
void GraphicalMaze::findStartAndEnd()
{
    const auto &grid = maze.getGrid();
    mazeHeight = grid.size();
    mazeWidth = grid[0].size();

    // Find start position (left edge)
    for (int row = 0; row < mazeHeight; row++)
    {
        if (grid[row][0] == ' ')
        {
            startRow = row;
            startCol = 0;
            playerRow = row;
            playerCol = 0;
            break;
        }
    }

    // Find end position (right edge)
    for (int row = 0; row < mazeHeight; row++)
    {
        if (grid[row][mazeWidth - 1] == ' ')
        {
            endRow = row;
            endCol = mazeWidth - 1;
            break;
        }
    }
}

// Initialize GLFW window
bool GraphicalMaze::initWindow()
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Calculate window size based on maze dimensions
    int windowWidth = mazeWidth * CELL_SIZE + WINDOW_PADDING * 2;
    int windowHeight = mazeHeight * CELL_SIZE + WINDOW_PADDING * 2;

    window = glfwCreateWindow(windowWidth, windowHeight, "Maze Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return false;
    }

    // Set up OpenGL viewport
    glViewport(0, 0, windowWidth, windowHeight);

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

// Public initialize method
bool GraphicalMaze::initialize()
{
    findStartAndEnd();
    return initWindow();
}

// Check if move is valid
bool GraphicalMaze::isValidMove(int row, int col) const
{
    const auto &grid = maze.getGrid();

    if (row < 0 || row >= mazeHeight || col < 0 || col >= mazeWidth)
    {
        return false;
    }

    if (grid[row][col] == '#')
    {
        return false;
    }

    return true;
}

// Draw a filled rectangle
void GraphicalMaze::drawRect(float x, float y, float width, float height, const Color &color)
{
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Draw the maze
void GraphicalMaze::drawMaze()
{
    const auto &grid = maze.getGrid();

    for (int row = 0; row < mazeHeight; row++)
    {
        for (int col = 0; col < mazeWidth; col++)
        {
            float x = WINDOW_PADDING + col * CELL_SIZE;
            float y = WINDOW_PADDING + row * CELL_SIZE;

            // Draw start position
            if (row == startRow && col == startCol)
            {
                drawRect(x, y, CELL_SIZE, CELL_SIZE, START_COLOR);
            }
            // Draw end position
            else if (row == endRow && col == endCol)
            {
                drawRect(x, y, CELL_SIZE, CELL_SIZE, END_COLOR);
            }
            // Draw wall
            else if (grid[row][col] == '#')
            {
                drawRect(x, y, CELL_SIZE, CELL_SIZE, WALL_COLOR);
            }
            // Draw path
            else
            {
                drawRect(x, y, CELL_SIZE, CELL_SIZE, PATH_COLOR);
            }

            // Draw grid lines for better visibility
            glColor4f(0.5f, 0.5f, 0.5f, 0.2f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + CELL_SIZE, y);
            glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
            glVertex2f(x, y + CELL_SIZE);
            glEnd();
        }
    }
}

// Draw the player
void GraphicalMaze::drawPlayer()
{
    float x = WINDOW_PADDING + playerCol * CELL_SIZE;
    float y = WINDOW_PADDING + playerRow * CELL_SIZE;

    // Draw player as a circle (approximated with triangle fan)
    float centerX = x + CELL_SIZE / 2.0f;
    float centerY = y + CELL_SIZE / 2.0f;
    float radius = CELL_SIZE * 0.35f;

    glColor4f(PLAYER_COLOR.r, PLAYER_COLOR.g, PLAYER_COLOR.b, PLAYER_COLOR.a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(centerX + cos(angle) * radius, centerY + sin(angle) * radius);
    }
    glEnd();

    // Draw player outline
    glColor4f(0.0f, 0.4f, 0.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(centerX + cos(angle) * radius, centerY + sin(angle) * radius);
    }
    glEnd();
    glLineWidth(1.0f);
}

// Draw win message overlay
void GraphicalMaze::drawWinMessage()
{
    if (!gameWon)
        return;

    // Draw semi-transparent overlay
    int windowWidth = mazeWidth * CELL_SIZE + WINDOW_PADDING * 2;
    int windowHeight = mazeHeight * CELL_SIZE + WINDOW_PADDING * 2;

    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw victory box
    float boxWidth = 400;
    float boxHeight = 150;
    float boxX = (windowWidth - boxWidth) / 2.0f;
    float boxY = (windowHeight - boxHeight) / 2.0f;

    // Box background
    glColor4f(0.2f, 0.8f, 0.3f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY + boxHeight);
    glVertex2f(boxX, boxY + boxHeight);
    glEnd();

    // Box border
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY + boxHeight);
    glVertex2f(boxX, boxY + boxHeight);
    glEnd();
    glLineWidth(1.0f);
}

// Render the game
void GraphicalMaze::render()
{
    glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    glClear(GL_COLOR_BUFFER_BIT);

    drawMaze();
    drawPlayer();

    if (gameWon)
    {
        drawWinMessage();
    }
}

// Main game loop
void GraphicalMaze::run()
{
    std::cout << "\n=== Graphical Maze Game Started ===" << std::endl;
    std::cout << "Navigate from the blue start to the orange end!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys or HJKL (vim style) - Move" << std::endl;
    std::cout << "  ESC or Q - Quit" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Thanks for playing!" << std::endl;
}
