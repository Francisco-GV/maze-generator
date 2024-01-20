#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Cell.h"

class Maze
{
public:
    Maze(int width, int height);
    void calculate();
    std::vector<std::vector<Cell>> getCells();

    int getWidth();
    int getHeight();
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
};

#endif
