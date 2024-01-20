#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Canvas
{
public:
    Canvas();
    void start();
    void draw();
    void update();
private:
    sf::RenderWindow window;
    Maze maze;
};

#endif // !CANVAS_H
