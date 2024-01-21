#include "Canvas.h"
#include <cstdlib>
#include <cstdio>

int main()
{
    long seed;
    srand(time(&seed));
    printf("seed: %ld\n", seed);

    Canvas canvas;

    canvas.start();
    return 0;
}
