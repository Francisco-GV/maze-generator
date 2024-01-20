#include "Maze.h"

Maze::Maze(int width, int height)
{
    cells.resize(height, std::vector<Cell>(width, Cell()));
}

void Maze::calculate()
{
    // TODO: do, lol
}
