#include <stack>

#include "algorithms/IterativeBacktracker.h"

void IterativeBacktracker::start(std::function<void()> callback)
{
    srand(seed);

    int first = random(0, maze.getWidth() - 1);
    calculate(0, first, callback);
}

void IterativeBacktracker::calculate(int y, int x, std::function<void()> callback)
{
    std::stack<std::shared_ptr<Cell>> stack;
    
    std::shared_ptr<Cell> initialCell = maze.getCells()[y][x];

    initialCell->setVisited();
    maze.increaseVisitedCells();
    stack.push(initialCell);

    if (callback != nullptr)
    {
        callback();
    }

    while (!stack.empty())
    {
        std::shared_ptr<Cell> currentCell = stack.top();
        int currentY = currentCell->getY();
        int currentX = currentCell->getX();
        
        std::vector<int> neighbors;
        if ((neighbors = maze.getUnvisitedNeighbors(currentY, currentX)).size() > 0)
        {
            stack.push(currentCell);

            int neighbor = randomInRange(neighbors);
            maze.setWall(currentY, currentX, neighbor, false);

            switch (neighbor)
            {
                case Wall::LEFT:  currentX -= 1; break;
                case Wall::RIGHT: currentX += 1; break;
                case Wall::UP:    currentY -= 1; break;
                case Wall::DOWN:  currentY += 1; break;
            }

            std::shared_ptr<Cell> chosenCell = maze.getCells()[currentY][currentX];

            chosenCell->setVisited();
            maze.increaseVisitedCells();

            if (callback != nullptr)
            {
                callback();
            }

            stack.push(chosenCell); 
        }
        else
        {
            stack.pop(); 

            currentCell->setSurrounded();
            maze.increaseVisitedCells();


            if (callback != nullptr)
            {
                callback();
            }
        }
    }
}

float IterativeBacktracker::calculatePercentage()
{
    // total cells multiplied by 2 to consider both visited cells and surrounded cells 
    // so as not to "stuck" the percentage
    return maze.getVisitedCells() * 100.f / ((maze.getWidth() * maze.getHeight()) * 2);
}
