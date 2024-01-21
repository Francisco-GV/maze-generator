#include <SFML/Graphics.hpp>
#include "Canvas.h"
#include "Maze.h"
#include "Cell.h"

// TODO: Change hardcoded values
Canvas::Canvas() : window(sf::VideoMode(500, 500), "Maze",
                          sf::Style::Titlebar | sf::Style::Close),
                    maze(20, 20)
{
    window.setFramerateLimit(60);
}

void Canvas::start()
{
    maze.calculate();
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
    
    sf::Vector2f size{window.getSize()};

    int hstep = size.x / maze.getWidth();
    int vstep = size.y / maze.getHeight();

    std::vector<std::vector<std::shared_ptr<Cell>>> cells = maze.getCells();

    for (int i = 0; i < cells.size(); i++)
    {
        for (int n = 0; n < cells[i].size(); n++)
        {
            std::shared_ptr<Cell> cell = cells[i][n];
            int y = i * vstep;
            int x = n * hstep;
           
            if (cell->getWall(Wall::LEFT))
            {
                sf::Vertex points[]
                {
                    sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x, y + vstep), sf::Color::Black)
                };
                window.draw(points, 2, sf::Lines);
            }

            if (cell->getWall(Wall::RIGHT))
            {
                sf::Vertex points[]
                {
                    sf::Vertex(sf::Vector2f(x + hstep, y), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x + hstep, y + vstep), sf::Color::Black)
                };
                window.draw(points, 2, sf::Lines);
            }

            if (cell->getWall(Wall::UP))
            {
                sf::Vertex points[]
                {
                    sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x + hstep, y), sf::Color::Black)
                };
                window.draw(points, 2, sf::Lines);
            }

            if (cell->getWall(Wall::DOWN))
            {
                sf::Vertex points[]
                {
                    sf::Vertex(sf::Vector2f(x, y + vstep), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x + hstep, y + vstep), sf::Color::Black)
                };
                window.draw(points, 2, sf::Lines);
            }
        }
    }

    window.display();
}
