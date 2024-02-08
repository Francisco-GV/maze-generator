#include "Cell.h"

Cell::Cell(int y, int x) : y(y), x(x)
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

void Cell::setSurrounded(bool surrounded)
{
    this->surrounded = surrounded;
}

bool Cell::isSurrounded()
{
    return surrounded;
}

bool Cell::getWall(int index)
{
    return walls[index];
}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}
