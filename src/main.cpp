#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "Canvas.h"
#include "Util.h"

int columns = 50;
int rows = 50;
int width = 500;
int height = 500;
int padding = 0;
unsigned int seed = 0;
bool animate = false;
int fps = 20;

void getArgs(int argc, char* argv[])
{
    int character;
    while ((character = getopt(argc, argv, "c:r:w:h:s:af:p:")) != -1)
    {
        long value = -1;
        isNumber(optarg, &value);
        
        if (value != -1 || character == 'a')
        {
            switch (character)
            {
                case 'a': animate = true; break;
                case 'c': columns = (int) value; break;
                case 'r': rows    = (int) value; break;
                case 'w': width   = (int) value; break;
                case 'h': height  = (int) value; break;
                case 'p': padding = (int) value; break;
                case 's': seed    = value; break;
                case 'f': fps  = (int) value; break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    getArgs(argc, argv);

    if (seed == 0)
    {
        // Potential data loss doesn't matter
        seed = (unsigned int) time(NULL);
    }

    printf("==== Maze Generator ====\n");
    printf("size: %dx%d\n", columns, rows);
    printf("window size: %dx%d\n", width, height);
    printf("seed: %ld\n", seed);
    printf("\nGenerating...\n");

    Maze maze(columns, rows, seed);
    // Add padding to width/height for the bottom/right border
    Canvas canvas(width + padding, height + padding, maze, padding, animate, fps);

    canvas.start();
    return 0;
}
