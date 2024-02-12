#ifndef KRUSKALALGORITHM_H
#define KRUSKALALGORITHM_H

#include "Algorithm.h"
#include <set>

struct Edge
{
    Edge(int y, int x, int wall, int weight);
    int x;
    int y;
    int wall;
    int weight;
};

struct Node
{
    Node(int parent, int rank);
    // In this case, the parent represents its index in the DisjointSet nodes array
    int parent;
    int rank;
};

class DisjointSet
{
public:
    DisjointSet(int height, int width);
    // Get the root of a node
    int find(int node);
    int find(int nodeY, int nodeX);
    void setUnion(int n1, int n2);
private:
    // Note: this actually represents a bidimensional array
    std::vector<Node> nodes;
    int width; // To calculate index with two values later
};

class KruskalAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void start(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
    float calculatePercentage() override;
private:
    size_t initialWallsSize;
    std::vector<Edge> edges; // More appropiate name
    // Pointer to initialize later
    std::unique_ptr<DisjointSet> disjointSet;
};

#endif
