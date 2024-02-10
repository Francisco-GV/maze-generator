#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <cstdlib>

inline float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (max2 - min2) * ((value - min1) / (max1 - min1));
}

bool isNumber(char* text, long* value);

#endif
