#include <SFML/Graphics.hpp>
#include <string>
#include "Canvas.h"
#include "algorithms/Algorithm.h"
#include "Maze.h"
#include "Cell.h"

// TODO: Change hardcoded values
Canvas::Canvas(int width, int height, Maze& maze, int padding, bool animate, unsigned int fps) : window(sf::VideoMode(width, height), "Maze",
                          sf::Style::Titlebar | sf::Style::Close), animate(animate), maze(maze), padding(padding)
{
    window.setFramerateLimit(fps);

    window.setTitle("Maze - Seed: " + std::to_string(maze.getAlgorithm()->getSeed()));
}

void Canvas::start()
{
    if (!animate)
    {
        maze.init(nullptr);    
    }
    else
    {
        // There's probably a better way to do this... hmmm
        // TODO: use threads (maybe?) to separate algorithm from drawing
        maze.init([this]()
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
    if (animate)
    {
        // total cells multiplied by 2 to consider both visited cells and surrounded cells 
        // so as not to "stuck" the percentage
        int percentage = (int)(maze.getVisitedCells() * 100.f / ((maze.getWidth() * maze.getHeight()) * 2));
        std::string title = "Maze - Seed: " + std::to_string(maze.getAlgorithm()->getSeed()) + 
            " - " + std::to_string(percentage) + "%"; 
        window.setTitle(title);
    }

    manageEvents();
}

void Canvas::draw()
{
    window.clear(sf::Color::Black);
    
    sf::Vector2f size{window.getSize()};

    int hstep = (size.x - padding) / maze.getWidth();
    int vstep = (size.y - padding) / maze.getHeight();

    std::vector<std::vector<std::shared_ptr<Cell>>> cells = maze.getCells();

    // Draw the cells first so that they don't paint over the padding border in certain corners
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
            }
        }
    }

    sf::Color wallColor = sf::Color::Black;
    // Now draw the walls
    for (int i = 0; i < cells.size(); i++)
    {
        for (int n = 0; n < cells[i].size(); n++)
        {
            std::shared_ptr<Cell> cell = cells[i][n];
            int y = i * vstep;
            int x = n * hstep;

            if (cell->wasAlreadyVisited())
            {
                // The right/bottom wall drawing was removed because almost each right/bottom wall was
                // the top/left wall of another.
                if (cell->getWall(Wall::LEFT))
                {
                    if (padding > 0)
                    {
                        // Add padding to height to join top-left corners
                        sf::RectangleShape border(sf::Vector2f(padding, vstep + padding));
                        border.setPosition(x, y);
                        border.setFillColor(wallColor);
                        window.draw(border);
                    }
                    else
                    {
                        sf::Vertex points[]
                        {
                            sf::Vertex(sf::Vector2f(x, y), wallColor),
                            sf::Vertex(sf::Vector2f(x, y + vstep), wallColor)
                        };
                        window.draw(points, 2, sf::Lines);
                    }
                }

                if (cell->getWall(Wall::UP))
                {
                    if (padding > 0)
                    {
                        // Add padding to width to join top-left corners
                        sf::RectangleShape border(sf::Vector2f(hstep + padding, padding));
                        border.setPosition(x, y);
                        border.setFillColor(wallColor);
                        window.draw(border);
                    }
                    else
                    {
                        sf::Vertex points[]
                        {
                            sf::Vertex(sf::Vector2f(x, y), wallColor),
                            sf::Vertex(sf::Vector2f(x + hstep, y), wallColor)
                        };
                        window.draw(points, 2, sf::Lines);
                    }
                }
            }
        }
    }

    if (padding > 0)
    {
        sf::RectangleShape rightBorder(sf::Vector2f(padding, size.y));
        rightBorder.setPosition(size.x - padding, 0);        
        rightBorder.setFillColor(wallColor);

        sf::RectangleShape bottomBorder(sf::Vector2f(size.x, padding));
        bottomBorder.setPosition(0, size.y - padding);        
        bottomBorder.setFillColor(wallColor);

        window.draw(rightBorder);
        window.draw(bottomBorder);
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
