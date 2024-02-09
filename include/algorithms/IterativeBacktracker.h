#ifndef ITERATIVEBACKTRACKER_H
#define ITERATIVEBACKTRACKER_H

#include "Algorithm.h"
#include <stack>

class IterativeBacktracker : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void start(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
    float calculatePercentage() override;
private:
    std::stack<std::shared_ptr<Cell>> stack;
};

#endif
