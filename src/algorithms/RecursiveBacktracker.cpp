#include "algorithms/RecursiveBacktracker.h"

void RecursiveBacktracker::start(std::function<void()> callback)
{
    // I suspect that some SFML component (for some reason) modifies 
    // the seed during its init (must check it)
    // So better set the seed just before starting the algorithm
    srand(seed);

    int first = random(0, maze.getWidth() - 1);
    // The maze will start at the top
    calculate(0, first, callback);
}

void RecursiveBacktracker::calculate(int y, int x, std::function<void()> callback)
{
    std::shared_ptr<Cell> cell = maze.getCells()[y][x];
    
    cell->setVisited();
    maze.increaseVisitedCells();
    if (callback != nullptr)
    {
        callback();
    }
    
    std::vector<int> neighbors; 
    while ((neighbors = maze.getUnvisitedNeighbors(y, x)).size() > 0)
    {
        int neighbor = randomInRange(neighbors);
        
        maze.setWall(y, x, neighbor, false);

        switch (neighbor)
        {
            case Wall::LEFT:
                calculate(y, x - 1, callback);
                break;
            case Wall::RIGHT:
                calculate(y, x + 1, callback);
                break;
            case Wall::UP:
                calculate(y - 1, x, callback);
                break;
            case Wall::DOWN:
                calculate(y + 1, x, callback);
                break;
        }
    }
    cell->setSurrounded();

    // All this has to be executed twice, when visited and when surrounded
    // to visualize the backtracking and update properly the percentage
    maze.increaseVisitedCells();
    if (callback != nullptr)
    {
        callback();
    }
}

float RecursiveBacktracker::calculatePercentage()
{
    // total cells multiplied by 2 to consider both visited cells and surrounded cells 
    // so as not to "stuck" the percentage
    return maze.getVisitedCells() * 100.f / ((maze.getWidth() * maze.getHeight()) * 2);
}
