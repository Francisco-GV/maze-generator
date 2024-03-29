#include "util/Util.h"
#include <cctype>

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
