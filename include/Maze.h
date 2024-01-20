#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Cell.h"

class Maze
{
public:
    Maze(int width, int height);
    void calculate();
private:
    std::vector<std::vector<Cell>> cells;
};

#endif
