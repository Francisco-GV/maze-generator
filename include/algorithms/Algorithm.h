#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <functional>
#include "../Maze.h"
#include "../Util.h"

class Algorithm
{
public:
    Algorithm(Maze& maze, unsigned int seed);
    virtual void init(std::function<void()> callback = nullptr);
    virtual void calculate(int y, int x, std::function<void()> callback = nullptr);

    unsigned int getSeed();
protected:
    Maze& maze;
    unsigned int seed;
};

#endif