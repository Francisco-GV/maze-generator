#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Canvas
{
public:
    Canvas(int width, int height, Maze& maze, int padding, bool animate, unsigned int fps);
    void start();
private:
    void draw();
    void update();
    void manageEvents();
    bool animate;
    int padding;
    sf::RenderWindow window;
    Maze maze;
};

#endif // !CANVAS_H
