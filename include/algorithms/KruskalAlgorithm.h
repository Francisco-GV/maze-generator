#ifndef KRUSKALALGORITHM_H
#define KRUSKALALGORITHM_H

#include "Algorithm.h"
#include <set>

struct Edge
{
    Edge(int y, int x, int wall);
    int x;
    int y;
    int wall;
};

class KruskalAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void init(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
    float calculatePercentage() override;
private:
    size_t initialWallsSize;
    std::vector<Edge> walls;
    std::vector<std::vector<std::set<std::shared_ptr<Cell>>>> sets;
};

#endif
