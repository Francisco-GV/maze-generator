#include "algorithms/Algorithm.h"

Algorithm::Algorithm(Maze& maze, unsigned int seed) : maze(maze), seed(seed)
{}

unsigned int Algorithm::getSeed()
{
    return seed;
}

float Algorithm::calculatePercentage()
{
    return 0;
}
