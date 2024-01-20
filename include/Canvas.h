#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>

class Canvas
{
public:
    Canvas();
    void start();
    void draw();
    void update();
private:
    sf::RenderWindow window;
};

#endif // !CANVAS_H
