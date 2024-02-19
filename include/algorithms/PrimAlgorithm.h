#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H

#include <vector>

#include "Algorithm.h"

// TODO: optimize algorithm
class PrimAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void start(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
    float calculatePercentage() override;
private:
    template <typename A, typename B> struct Pair
    {
        Pair(A a, B b) : a(a), b(b)
        {}
        A a;
        B b;
    };

    struct Edge
    {
        Edge(int y, int x, int wall, int weight);
        int y;
        int x;
        int wall;
        int weight;
    };

    struct Graph
    {
        std::vector<std::shared_ptr<Edge>> edges;
    };


    Pair<std::shared_ptr<Edge>, int> getMinEdge();
    std::vector<std::vector<Graph>> nodes;
    std::vector<std::shared_ptr<Edge>> edges;

};

#endif
