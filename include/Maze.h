#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <functional>
#include <memory>
#include "Cell.h"

class Algorithm;
class Maze
{
public:
    Maze(int width, int height);
    void init(std::function<void()> callback);
    std::vector<std::vector<std::shared_ptr<Cell>>>& getCells();
    std::vector<int> getUnvisitedNeighbors(int y, int x);

    void setAlgorithm(std::shared_ptr<Algorithm> algorithm);

    void setWall(int y, int x, int wall, bool set);
    void increaseVisitedCells();

    int getWidth();
    int getHeight();
    int getVisitedCells();
    std::shared_ptr<Algorithm> getAlgorithm();
private:
    void calculate(int y, int x, std::function<void()> callback);
    int width;
    int height;
    int visitedCells = 0;
    std::shared_ptr<Algorithm> algorithm;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};

#endif
