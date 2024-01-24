#include <SFML/Graphics.hpp>
#include "Canvas.h"
#include "Maze.h"
#include "Cell.h"

// TODO: Change hardcoded values
Canvas::Canvas(int width, int height, Maze& maze, bool animate, unsigned int fps) : window(sf::VideoMode(width, height), "Maze",
                          sf::Style::Titlebar | sf::Style::Close), animate(animate), maze(maze)
{
    window.setFramerateLimit(fps);
}

void Canvas::start()
{
    if (!animate)
    {
        maze.calculate(nullptr);    
    }
    else
    {
        // There's probably a better way to do this... hmmm
        // TODO: use threads (maybe?) to separate algorithm from drawing
        maze.calculate([this]()
        {
            if (window.isOpen())
            {
                this->update();
                this->draw();
            }
        });
    }

    while (window.isOpen())
    {
        update();
        draw();
    }
}

void Canvas::update()
{
    manageEvents();
}

void Canvas::draw()
{
    window.clear(sf::Color::Black);
    
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

            if (cell->wasAlreadyVisited())
            {
                sf::RectangleShape rectangle(sf::Vector2f(hstep, vstep));
                rectangle.setPosition(x, y);
                rectangle.setFillColor((animate && cell->isSurrounded()) ? sf::Color(63, 63, 255, 255) : sf::Color::White);

                window.draw(rectangle);
            
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
    }

    window.display();
}

void Canvas::manageEvents()
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                // ¯\_(ツ)_/¯
                break;
        }
    }
}
