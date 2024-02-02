#include "algorithms/Algorithm.h"

Algorithm::Algorithm(Maze& maze, unsigned int seed) : maze(maze), seed(seed)
{}

void Algorithm::init(std::function<void()> callback)
{}

void Algorithm::calculate(int y, int x, std::function<void()> callback)
{}

unsigned int Algorithm::getSeed()
{
    return seed;
}