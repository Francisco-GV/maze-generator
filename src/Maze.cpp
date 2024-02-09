#include "Maze.h"
#include "algorithms/Algorithm.h"
#include "Util.h"
Maze::Maze(int width, int height) : width(width), height(height)
{
    for (int i = 0; i < height; i++)
    {
        std::vector<std::shared_ptr<Cell>> row;
        for (int n = 0; n < width; n++)
        {
            row.push_back(std::make_shared<Cell>(i, n));
        }

        cells.push_back(row);
    }
}

void Maze::setAlgorithm(std::shared_ptr<Algorithm> algorithm)
{
    this->algorithm = algorithm;
}

std::vector<std::vector<std::shared_ptr<Cell>>>& Maze::getCells()
{
    return cells;
}

void Maze::start(std::function<void()> callback)
{
    algorithm->start(callback);
}

void Maze::setWall(int y, int x, int wall, bool set)
{
    cells[y][x]->setWall(wall, set);
    
    switch (wall)
    {
        case Wall::LEFT:
            if (x - 1 >= 0)
            {
                cells[y][x - 1]->setWall(Wall::RIGHT, set);
            }
            break;
        case Wall::RIGHT:
            if (x + 1 < width)
            {
                cells[y][x + 1]->setWall(Wall::LEFT, set);
            }
            break;
        case Wall::UP:
            if (y - 1 >= 0)
            {
                cells[y - 1][x]->setWall(Wall::DOWN, set);
            }
            break;
        case Wall::DOWN:
            if (y + 1 < height)
            {
                cells[y + 1][x]->setWall(Wall::UP, set);
            }
            break;
    }
}

void Maze::increaseVisitedCells()
{
    visitedCells++;
}

int Maze::getWidth()
{
    return width;
}

int Maze::getHeight()
{
    return height;
}

int Maze::getVisitedCells()
{
    return visitedCells;
}

std::shared_ptr<Algorithm> Maze::getAlgorithm()
{
    return algorithm;
}

std::vector<int> Maze::getUnvisitedNeighbors(int y, int x)
{
    std::vector<int> unvisitedNeighbours;
    if (x - 1 >= 0)
    {
        if (!cells[y][x - 1]->wasAlreadyVisited())
        {
            unvisitedNeighbours.push_back(Wall::LEFT);
        }
    }

    if (x + 1 < width)
    {
        if (!cells[y][x + 1]->wasAlreadyVisited())
        {
            unvisitedNeighbours.push_back(Wall::RIGHT);
        }
    }

    if (y - 1 >= 0)
    {
        if (!cells[y - 1][x]->wasAlreadyVisited())
        {
            unvisitedNeighbours.push_back(Wall::UP);
        }
    }

    if (y + 1 < height)
    {
        if (!cells[y + 1][x]->wasAlreadyVisited())
        {
            unvisitedNeighbours.push_back(Wall::DOWN);
        }
    }

    return unvisitedNeighbours;
}
