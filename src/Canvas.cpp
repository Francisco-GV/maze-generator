#include "Canvas.h"
#include <SFML/Graphics.hpp>

Canvas::Canvas() : window(sf::VideoMode(500, 500), "Maze",
                          sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(60);
}

void Canvas::start()
{
    while (window.isOpen())
    {
        update();
        draw();
    }
}

void Canvas::update()
{
}

void Canvas::draw()
{
    window.clear(sf::Color::White);
    window.display();
}
