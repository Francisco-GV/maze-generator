#include <limits>

#include "algorithms/PrimAlgorithm.h"

PrimAlgorithm::Edge::Edge(int y, int x, int wall, int weight): y(y), x(x), 
    wall(wall), weight(weight)
{
}

void PrimAlgorithm::start(std::function<void()> callback)
{
    random.setSeed(seed);

    for (int y = 0; y < maze.getHeight(); y++)
    {
        std::vector<Graph> row;
        for (int x = 0; x < maze.getWidth(); x++)
        {
            Graph node;
            if (x > 0)
            {
                node.edges.push_back(std::make_shared<Edge>(y, x, Wall::LEFT, random.get()));
            }

            if (x < maze.getWidth() - 1)
            {
                node.edges.push_back(std::make_shared<Edge>(y, x, Wall::RIGHT, random.get()));
            }

            if (y > 0)
            {
                node.edges.push_back(std::make_shared<Edge>(y, x, Wall::UP, random.get()));
            }

            if (y < maze.getHeight() - 1)
            {
                node.edges.push_back(std::make_shared<Edge>(y, x, Wall::DOWN, random.get()));
            }

            row.push_back(node);
        }

        nodes.push_back(row);
    }

    int firstY = random.getInRange(0, maze.getHeight() - 1);
    int firstX = random.getInRange(0, maze.getWidth() - 1);

    calculate(firstY, firstX, callback);
}

void PrimAlgorithm::calculate(int y, int x, std::function<void()> callback) {
    std::vector<std::vector<std::shared_ptr<Cell>>>& cells = maze.getCells(); 

    cells[y][x]->setVisited();
    maze.increaseVisitedCells();

    cells[y][x]->setSurrounded();
    if (callback != nullptr) {
        callback();
    }
    cells[y][x]->setSurrounded(false);

    edges.insert(edges.end(), nodes[y][x].edges.begin(), nodes[y][x].edges.end());

    while (!edges.empty())
    {
        Pair<std::shared_ptr<Edge>, int> minEdge = getMinEdge(); 

        y = minEdge.a->y;
        x = minEdge.a->x;
        int dy = y;
        int dx = x;

        switch (minEdge.a->wall)
        {
            case Wall::LEFT:    dx--; break;
            case Wall::RIGHT:   dx++; break;
            case Wall::UP:      dy--; break;
            case Wall::DOWN:    dy++; break;
        }
        
        if (!cells[dy][dx]->wasAlreadyVisited())
        {
            maze.setWall(y, x, minEdge.a->wall, false);

            cells[dy][dx]->setVisited();
            maze.increaseVisitedCells();

            cells[dy][dx]->setSurrounded();
            if (callback != nullptr) {
                callback();
            }
            cells[dy][dx]->setSurrounded(false);

            edges.insert(edges.end(), nodes[dy][dx].edges.begin(), nodes[dy][dx].edges.end());
        }

        edges.erase(edges.begin() + minEdge.b);
    }
}

float PrimAlgorithm::calculatePercentage()
{
    return maze.getVisitedCells() * 100.f / ((maze.getWidth() * maze.getHeight()));
}

PrimAlgorithm::Pair<std::shared_ptr<PrimAlgorithm::Edge>, int> PrimAlgorithm::getMinEdge()
{
    int minWeight = std::numeric_limits<int>::max();
    std::shared_ptr<Edge> minEdge;
    int index = -1;

    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i]->weight <= minWeight)
        {
            minEdge = edges[i];
            minWeight = minEdge->weight;
            index = i;
        }
    }

    return Pair(minEdge, index);
}
