#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "Canvas.h"
#include <Util.h>

int columns = 50;
int rows = 50;
int width = 500;
int height = 500;
long seed = -1;

void getArgs(int argc, char* argv[])
{
    int character;
    while ((character = getopt(argc, argv, "c:r:w:h:s:")) != -1)
    {
        long value = -1;
        isNumber(optarg, &value);
        
        if (value != -1)
        {
            switch (character)
            {
                case 'c': columns = (int) value; break;
                case 'r': rows    = (int) value; break;
                case 'w': width   = (int) value; break;
                case 'h': height  = (int) value; break;
                case 's': seed    = value; break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    getArgs(argc, argv);
    
    if (seed == -1)
    {
        srand(time(&seed));
    }
    
    printf("==== Maze Generator ====\n");
    printf("size: %dx%d\n", columns, rows);
    printf("window size: %dx%d\n", width, height);
    printf("seed: %ld\n", seed);
    printf("\nGenerating...\n");

    Maze maze(columns, rows);
    Canvas canvas(width, height, maze);

    canvas.start();
    return 0;
}
