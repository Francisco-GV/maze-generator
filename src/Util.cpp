#include "Util.h"

int randomInRange(std::vector<int> values)
{
    int i = random(0, values.size() - 1);

    return values[i];
}
