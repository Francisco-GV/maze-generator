#include "Util.h"
#include <cctype>

int randomInRange(std::vector<int> values)
{
    int i = random(0, values.size() - 1);

    return values[i];
}

bool isNumber(char* text, long* value)
{
    if (text == nullptr)
    {
        return false;
    }

    char* original = text;
    char c;
    while ((c = *text++) != '\0')
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    *value = atol(original);

    return true;
}
