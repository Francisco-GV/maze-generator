#ifndef RECURSIVEBACKTRACKER_H
#define RECURSIVEBACKTRACKER_H

#include "Algorithm.h"

class RecursiveBacktracker : public Algorithm
{
public:
    RecursiveBacktracker(Maze& maze, unsigned int seed);
    void init(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
};

#endif