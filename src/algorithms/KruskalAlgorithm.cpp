#include <vector>
#include <set>
#include <algorithm>

#include "algorithms/KruskalAlgorithm.h"
#include "util/Util.h"

KruskalAlgorithm::Edge::Edge(int y, int x, int wall, int weight): x(x), y(y), 
    wall(wall), weight(weight)
{}

KruskalAlgorithm::Node::Node(int parent, int rank): parent(parent), rank(rank)
{}

KruskalAlgorithm::DisjointSet::DisjointSet(int height, int width) : width(width)
{
    for (int y = 0; y < height; y++)
    {
        std::vector<Node> row;
        for (int x = 0; x < width; x++)
        {
            // since each node is the first element of its set, is its own parent (root)
            nodes.emplace_back(y * width + x, 0);
        }
    }    
}

int KruskalAlgorithm::DisjointSet::find(int node)
{
    if (nodes[node].parent != node)
    {
        // Path compression
        nodes[node].parent = find(nodes[node].parent);
        return nodes[node].parent;
    }
    
    return node;
}

int KruskalAlgorithm::DisjointSet::find(int nodeY, int nodeX)
{
    return find(nodeY * width + nodeX);
}

void KruskalAlgorithm::DisjointSet::setUnion(int n1, int n2)
{
    // This may be unnecessary because where the function is called, this
    // has already been done, but I want to keep the function "independent" 
    n1 = find(n1);
    n2 = find(n2);

    if (n1 == n2)
    {
        return;
    }

    if (nodes[n1].rank < nodes[n2].rank)
    {
        // Swap nodes to ensure that n1 has the larger rank tree
        int tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    else if (nodes[n1].rank == nodes[n2].rank)
    {
        nodes[n1].rank++;
    }

    nodes[n2].parent = n1; 

}

void KruskalAlgorithm::start(std::function<void()> callback)
{
    random.setSeed(seed);

    for (int y = 0; y < maze.getHeight(); y++)
    {
        for (int x = 0; x < maze.getWidth(); x++)
        {
            // Add only inner edges (between (1,1) and (height - 1, width - 1))
            // And set a random weight to them
            if (y > 0)
            {
                edges.emplace_back(y, x, Wall::UP, random.get());
            }

            if (x > 0)
            {
                edges.emplace_back(y, x, Wall::LEFT, random.get());
            }
        }
    }

    initialWallsSize = edges.size();

    // Sort in descending order to pop the elements when they are used
    // (only to calculate the percentage with the edges size)
    std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2) { return e1.weight > e2.weight; });
    disjointSet = std::make_unique<DisjointSet>(maze.getHeight(), maze.getWidth());

    calculate(-1, -1, callback);
}

void KruskalAlgorithm::calculate(int y, int x, std::function<void()> callback)
{
    std::vector<std::vector<std::shared_ptr<Cell>>>& cells = maze.getCells();

    while (!edges.empty())
    {
        Edge& edge = edges.back();
        edges.pop_back();

        cells[edge.y][edge.x]->setVisited();
        cells[edge.y][edge.x]->setSurrounded();
        if (callback != nullptr) {
            callback();
        }

        int dx = edge.wall == Wall::LEFT ? -1 : 0;
        int dy = edge.wall == Wall::UP ? -1 : 0;

        cells[edge.y + dy][edge.x + dx]->setVisited();
        cells[edge.y + dy][edge.x + dx]->setSurrounded();
        if (callback != nullptr)
        {
            callback();
        }

        int n1 = disjointSet->find(edge.y, edge.x);
        int n2 = disjointSet->find(edge.y + dy, edge.x + dx);

        if (n1 != n2)
        {
            disjointSet->setUnion(n1, n2);

            maze.setWall(edge.y, edge.x, edge.wall, false);

            if (callback != nullptr)
            {
                callback();
            }
        }
        cells[edge.y][edge.x]->setSurrounded(false);
        cells[edge.y + dy][edge.x + dx]->setSurrounded(false);
    }
}

float KruskalAlgorithm::calculatePercentage()
{
    return map(edges.size(), initialWallsSize, 0, 0.f, 100.f);
}
