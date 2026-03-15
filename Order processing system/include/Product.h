#ifndef Product_h
#define Product_h
#include "Constant.h"
#include "Unit.h"
#include <array>

class Product : public Unit
{
private:
    std::array<int, 4> compIds;
    int cycles;

public:
    Product(int id = -1, std::array<int, 4> comps = {0, 0, 0, 0}, int cyc = 0) : Unit(id, 0), compIds(comps), cycles(cyc) {}
    std::array<int, 4> getComponents() const { return compIds; }
    int getCycles() const { return cycles; }

    double calculatePCCost(const int compCosts[]) const
    {
        double cost = 0;
        for (int i = 0; i < 4; i++)
            cost += compCosts[compIds[i]];
        cost += cycles * RUNNING_COST_PER_CYCLE;
        return cost;
    }
};

#endif