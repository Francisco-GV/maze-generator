#include "Maze.h"

Maze::Maze(int width, int height) : width(width), height(height)
{
    cells.resize(height, std::vector<Cell>(width, Cell()));
}

std::vector<std::vector<Cell>> Maze::getCells()
{
    return cells;
}

void Maze::calculate()
{
    // TODO: do, lol
}

int Maze::getWidth()
{
    return width;
}

int Maze::getHeight()
{
    return height;
}
