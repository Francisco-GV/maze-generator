#include "util/Random.h"

void Random::setSeed(long seed)
{
    generator.seed(seed);
}

int Random::getInRange(int lower, int upper)
{
    return (get() % (upper - lower + 1)) + lower;
}

int Random::getInVector(std::vector<int>& values)
{
    int i = getInRange(0, values.size() - 1);

    return values[i];
}

int Random::get()
{
    return distribution(generator);
}

std::mt19937& Random::getGenerator()
{
    return generator;
}
