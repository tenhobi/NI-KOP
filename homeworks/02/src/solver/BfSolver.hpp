#ifndef INC_01_BFSOLVER_HPP
#define INC_01_BFSOLVER_HPP


#include "Solver.hpp"

class BfSolver : public Solver {
public:
    bool shouldContinue(Bag bag,
                        Item item,
                        unsigned long usedWeight,
                        unsigned long collectedCost,
                        unsigned long estimate) const override {
        return true;
    }
};


#endif //INC_01_BFSOLVER_HPP
