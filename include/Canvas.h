#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Canvas
{
public:
    Canvas(int width, int height, Maze& maze);
    void start();
private:
    void draw();
    void update();
    void manageEvents();
    sf::RenderWindow window;
    Maze maze;
};

#endif // !CANVAS_H
