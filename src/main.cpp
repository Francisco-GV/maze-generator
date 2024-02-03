#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <string>
#include "Canvas.h"
#include "Util.h"
#include "algorithms/Algorithm.h"
#include "algorithms/IterativeBacktracker.h"
#include "algorithms/RecursiveBacktracker.h"

int columns = 50;
int rows = 50;
int width = 500;
int height = 500;
int padding = 0;
unsigned int seed = 0;
bool animate = false;
int fps = 20;

std::array<std::string, 2> methods {
    "IterativeBacktracker", "RecursiveBacktracker"
};
std::string method = methods[0];


void getArgs(int argc, char* argv[])
{
    int character;
    while ((character = getopt(argc, argv, "c:r:w:h:s:af:p:m:")) != -1)
    {
        if (optarg)
        {
            long value = -1;
            if (isNumber(optarg, &value))
            {
                switch (character)
                {
                    case 'c': columns = (int) value; break;
                    case 'r': rows    = (int) value; break;
                    case 'w': width   = (int) value; break;
                    case 'h': height  = (int) value; break;
                    case 'p': padding = (int) value; break;
                    case 's': seed    = value; break;
                    case 'f': fps  = (int) value; break;
                }
            }
            else
            {
                std::string args(optarg);
                if (character == 'm')
                {
                    bool found;

                    for (int i = 0; i < methods.size(); i++)
                    {
                        if (methods[i] == args)
                        {
                            found = true;
                            method = args;
                        }
                    }

                    if (!found)
                    {
                        printf("Unknown method \"%s\", using %s\n", args.data(), method.data());
                    }
                }
            }
        }
        else
        {
            if (character == 'a')
            {
                animate = true;
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
    printf("Algorithm: %s\n", method.data());
    printf("seed: %ld\n", seed);

    Maze maze(columns, rows);

    Algorithm* algorithm;
    if (method == "IterativeBacktracker")
    {
        algorithm = new IterativeBacktracker(maze, seed);
    }
    else if (method == "RecursiveBacktracker")
    {
        algorithm = new RecursiveBacktracker(maze, seed);
    }

    maze.setAlgorithm(std::shared_ptr<Algorithm>(algorithm));

    // Add padding to width/height for the bottom/right border
    Canvas canvas(width + padding, height + padding, maze, padding, animate, fps);

    printf("\nGenerating...\n");
    canvas.start();
    return 0;
}
