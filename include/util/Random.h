#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
    void setSeed(long seed);
    int getInRange(int lower, int upper);
    int getInVector(std::vector<int>& values);

    std::mt19937 getGenerator();
private:
    std::mt19937 generator;
};

#endif