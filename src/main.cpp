// TODO: replace args parser with a platform-independent one
#include <unistd.h>

#include <chrono>
#include <array>
#include <string>
#include <iostream>

#include "algorithms/Algorithm.h"
#include "algorithms/IterativeBacktracker.h"
#include "algorithms/RecursiveBacktracker.h"
#include "algorithms/KruskalAlgorithm.h"
#include "algorithms/PrimAlgorithm.h"
#include "util/Util.h"
#include "Canvas.h"

int columns = 50;
int rows = 50;
int width = 500;
int height = 500;
int padding = 0;
long seed = 0;
bool animate = false;
int fps = 20;

std::array<std::string, 4> methods {
    "IterativeBacktracker", "RecursiveBacktracker", "KruskalAlgorithm", "PrimAlgorithm"
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
                        std::cout << "Unknown method \"" << args << "\"" << ", using " << method << "\n";
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
        std::chrono::duration duration = std::chrono::system_clock::now().time_since_epoch();
        seed = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }
    
    std::cout << "==== Maze Generator ====\n" <<
        "Size: "         << columns << "x" << rows << "\n" <<
        "Windows size: " << width << "x" << height << "\n" <<
        "Algorithm: "    << method                 << "\n" <<
        "Seed: "         << seed                   << "\n";

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
    else if (method == "KruskalAlgorithm")
    {
        algorithm = new KruskalAlgorithm(maze, seed);
    }
    else if (method == "PrimAlgorithm")
    {
        algorithm = new PrimAlgorithm(maze, seed);
    }

    maze.setAlgorithm(std::shared_ptr<Algorithm>(algorithm));

    // Add padding to width/height for the bottom/right border
    Canvas canvas(width + padding, height + padding, maze, padding, animate, fps);

    std::cout << "\nGenerating...\n";
    canvas.start();
    return 0;
}
