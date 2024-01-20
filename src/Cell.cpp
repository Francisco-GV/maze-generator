#include "Cell.h"

Cell::Cell()
{
    visited = false;
    for (int i = 0; i < 4; i++)
    {
        walls[i] = true;
    }
}

void Cell::setWall(int index, bool visible)
{
    walls[index] = visible;
}

void Cell::setVisited()
{
    visited = true;
}

bool Cell::wasAlreadyVisited()
{
    return visited;
}

bool Cell::getWall(int index)
{
    return walls[index];
}
