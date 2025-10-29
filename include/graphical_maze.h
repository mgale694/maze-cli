#ifndef GRAPHICAL_MAZE_H
#define GRAPHICAL_MAZE_H

#include "builder.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GraphicalMaze
{
private:
    Maze &maze;
    GLFWwindow *window;
    int playerRow;
    int playerCol;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    int mazeWidth;
    int mazeHeight;
    bool gameWon;

    // Rendering constants
    static constexpr int CELL_SIZE = 20;
    static constexpr int WINDOW_PADDING = 40;

    // Colors
    struct Color
    {
        float r, g, b, a;
    };
    static constexpr Color WALL_COLOR = {0.2f, 0.2f, 0.2f, 1.0f};
    static constexpr Color PATH_COLOR = {0.9f, 0.9f, 0.9f, 1.0f};
    static constexpr Color PLAYER_COLOR = {0.0f, 0.8f, 0.2f, 1.0f};
    static constexpr Color START_COLOR = {0.2f, 0.6f, 1.0f, 1.0f};
    static constexpr Color END_COLOR = {1.0f, 0.6f, 0.0f, 1.0f};
    static constexpr Color BG_COLOR = {0.1f, 0.1f, 0.15f, 1.0f};

    // Private methods
    bool initWindow();
    void findStartAndEnd();
    bool isValidMove(int row, int col) const;
    void handleInput();
    void render();
    void drawRect(float x, float y, float width, float height, const Color &color);
    void drawMaze();
    void drawPlayer();
    void drawWinMessage();

    // GLFW callbacks (need to be static)
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void errorCallback(int error, const char *description);

public:
    GraphicalMaze(Maze &m);
    ~GraphicalMaze();

    bool initialize();
    void run();
};

#endif // GRAPHICAL_MAZE_H
