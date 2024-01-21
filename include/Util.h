#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <cstdlib>

inline int random(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int randomInRange(std::vector<int> values);

#endif
