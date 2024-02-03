#ifndef ITERATIVEBACKTRACKER_H
#define ITERATIVEBACKTRACKER_H

#include "Algorithm.h"

class IterativeBacktracker : public Algorithm
{
public:
    using Algorithm::Algorithm;
    void init(std::function<void()> callback = nullptr) override;
    void calculate(int y, int x, std::function<void()> callback = nullptr) override;
};

#endif