#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <functional>
#include <memory>
#include "Cell.h"

class Maze
{
public:
    Maze(int width, int height, unsigned int seed);
    void calculate(std::function<void()> callback);
    std::vector<std::vector<std::shared_ptr<Cell>>>& getCells();
    std::vector<int> getUnvisitedNeighbors(int y, int x);

    int getWidth();
    int getHeight();
    int getSeed();
    int getVisitedCells();
private:
    void recursiveBacktracker(int y, int x, std::function<void()> callback);
    void setWall(int y, int x, int wall, bool set);
    int width;
    int height;
    unsigned int seed;
    int visitedCells = 0;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};

#endif
