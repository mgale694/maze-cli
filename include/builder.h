#ifndef BUILDER_H
#define BUILDER_H

#include <vector>

void buildMaze();
std::vector<std::vector<char>> createGrid(int width, int height);
void debugPrintGrid(const std::vector<std::vector<char>> &grid);

#endif // BUILDER_H
