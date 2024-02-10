#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <functional>

#include "../Maze.h"
#include "../util/Random.h"

class Algorithm
{
public:
    Algorithm(Maze& maze, unsigned int seed);
    virtual void start(std::function<void()> callback = nullptr) = 0;
    virtual void calculate(int y, int x, std::function<void()> callback = nullptr) = 0;

    unsigned int getSeed();
    virtual float calculatePercentage();
protected:
    Maze& maze;
    Random random;
    unsigned int seed;
};

#endif
