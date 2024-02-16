#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H

#include <vector>

#include "Algorithm.h"

template <typename A, typename B> struct Pair
{
    Pair(A a, B b) : a(a), b(b)
    {}
    A a;
    B b;
};

// TODO: use namespaces to avoid redefinitions
struct NodeEdge
{
    NodeEdge(int y, int x, int wall, int weight);
    int y;
    int x;
    int wall;
    int weight;
};

struct GraphNode
{
    std::vector<std::shared_ptr<NodeEdge>> edges;
};

// TODO: optimize algorithm
class PrimAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void start(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
    float calculatePercentage() override;
private:
    Pair<std::shared_ptr<NodeEdge>, int> getMinEdge();
    std::vector<std::vector<GraphNode>> nodes;
    std::vector<std::shared_ptr<NodeEdge>> edges;
};

#endif
