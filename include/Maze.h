#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <memory>
#include "Cell.h"

class Maze
{
public:
    Maze(int width, int height);
    void calculate();
    std::vector<std::vector<std::shared_ptr<Cell>>>& getCells();
    std::vector<int> getUnvisitedNeighbors(int y, int x);

    int getWidth();
    int getHeight();
private:
    void recursiveBacktracker(int y, int x);
    void setWall(int y, int x, int wall, bool set);
    int width;
    int height;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};

#endif
