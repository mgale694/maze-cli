#ifndef BUILDER_H
#define BUILDER_H

#include <vector>

class Maze {
private:
  int width;
  int height;
  int startRow;
  int endRow;
  std::vector<std::vector<char>> grid;
  
  void createGrid();
  void placeStartEnd();
  void createCorrectPath();
  void fillRandomPaths(int percentage);
  int pickRandomRow();

public:
  Maze(int w, int h);
  void generate();
  void debugPrint() const;
  const std::vector<std::vector<char>>& getGrid() const;
};

#endif // BUILDER_H
