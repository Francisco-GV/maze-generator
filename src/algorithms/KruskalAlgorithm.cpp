#include "algorithms/KruskalAlgorithm.h"
#include <vector>
#include <set>
#include <cstdio>

Edge::Edge(int y, int x, int wall): x(x), y(y), wall(wall)
{}

void KruskalAlgorithm::init(std::function<void()> callback)
{
    for (int y = 0; y < maze.getHeight(); y++)
    {
        for (int x = 0; x < maze.getWidth(); x++)
        {
            if (y > 0)
            {
                walls.emplace_back(y, x, Wall::UP);
            }

            if (x > 0)
            {
                walls.emplace_back(y, x, Wall::LEFT);
            }
        }
    }

    for (int i = 0; i < maze.getHeight(); i++)
    {
        std::vector<std::set<std::shared_ptr<Cell>>> row;
        for (int n = 0; n < maze.getWidth(); n++)
        {
            std::set<std::shared_ptr<Cell>> setCell;
            setCell.insert(maze.getCells()[i][n]);

            row.push_back(std::set<std::shared_ptr<Cell>>(setCell));
        }

        sets.push_back(row);
    }

    srand(seed);
    calculate(-1, -1, callback);
}

void KruskalAlgorithm::calculate(int y, int x, std::function<void()> callback)
{
    while (!walls.empty())
    {
        int i = random(0, walls.size() - 1);
        Edge edge = walls[i];
        walls.erase(walls.begin() + i);

        maze.getCells()[edge.y][edge.x]->setVisited();
        if (callback != nullptr) {
            callback();
        }

        int dx = edge.wall == Wall::LEFT ? -1 : 0;
        int dy = edge.wall == Wall::UP ? -1 : 0;

        maze.getCells()[edge.y + dy][edge.x + dx]->setVisited();
        if (callback != nullptr)
        {
            callback();
        }

        std::set<std::shared_ptr<Cell>>& set1 = sets[edge.y][edge.x];
        std::set<std::shared_ptr<Cell>>& set2 = sets[edge.y + dy][edge.x + dx];

        if (set1 != set2)
        {
            set1.insert(set2.begin(), set2.end());
            
            std::set<std::shared_ptr<Cell>>::iterator it;
            for (it = set1.begin(); it != set1.end(); ++it)
            {
                std::shared_ptr<Cell> cell = *it; 

                int y = cell->getY();
                int x = cell->getX();

                sets[y][x] = set1;
            }

            maze.setWall(edge.y, edge.x, edge.wall, false);

            if (callback != nullptr)
            {
                callback();
            }
        }
    }
}