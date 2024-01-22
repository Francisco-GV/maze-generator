#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Canvas
{
public:
    Canvas(int width, int height, Maze& maze);
    void start();
    void draw();
    void update();
private:
    sf::RenderWindow window;
    Maze maze;
};

#endif // !CANVAS_H
