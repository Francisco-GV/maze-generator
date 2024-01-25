#include "Maze.h"
#include "Util.h"
Maze::Maze(int width, int height, unsigned int seed) : width(width), height(height), seed(seed)
{
    for (int i = 0; i < height; i++)
    {
        std::vector<std::shared_ptr<Cell>> row;
        for (int n = 0; n < width; n++)
        {
            row.push_back(std::make_shared<Cell>());
        }

        cells.push_back(row);
    }
}

std::vector<std::vector<std::shared_ptr<Cell>>>& Maze::getCells()
{
    return cells;
}

void Maze::calculate(std::function<void()> callback)
{
    // I suspect that some SFML component (for some reason) modifies 
    // the seed during its init (must check it)
    // So better set the seed just before starting the algorithm
    srand(seed);

    int first = random(0, width - 1);
    // The maze will start at the top
    recursiveBacktracker(0, first, callback);
}

void Maze::recursiveBacktracker(int y, int x, std::function<void()> callback)
{
    std::shared_ptr<Cell> cell = cells[y][x];
    
    cell->setVisited();
    visitedCells++;
    if (callback != nullptr)
    {
        callback();
    }
    
    std::vector<int> neighbors; 
    while ((neighbors = getUnvisitedNeighbors(y, x)).size() > 0)
    {
        int neighbor = randomInRange(neighbors);
        
        setWall(y, x, neighbor, false);

        switch (neighbor)
        {
            case Wall::LEFT:
                recursiveBacktracker(y, x - 1, callback);
                break;
            case Wall::RIGHT:
                recursiveBacktracker(y, x + 1, callback);
                break;
            case Wall::UP:
                recursiveBacktracker(y - 1, x, callback);
                break;
            case Wall::DOWN:
                recursiveBacktracker(y + 1, x, callback);
                break;
        }
    }
    cell->setSurrounded();

    // All this has to be executed twice, when visited and when surrounded
    // to visualize the backtracking and update properly the percentage
    visitedCells++;
    if (callback != nullptr)
    {
        callback();
    }
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

int Maze::getWidth()
{
    return width;
}

int Maze::getHeight()
{
    return height;
}

int Maze::getSeed()
{
    return seed;
}

int Maze::getVisitedCells()
{
    return visitedCells;
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
