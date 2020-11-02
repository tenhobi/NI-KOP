#ifndef INC_01_BNBSOLVER_HPP
#define INC_01_BNBSOLVER_HPP


#include "Solver.hpp"

class BnbSolver : public Solver {
public:
    bool shouldContinue(Bag bag,
                        Item item,
                        unsigned long usedWeight,
                        unsigned long collectedCost,
                        unsigned long estimateCostOfLeftItems) const override {
        // Cost can never be lower than minimal cost.
        if (estimateCostOfLeftItems + collectedCost < bag.getMinimalCost()) {
            return false;
        }

        // Weight is already bigger than the bag capacity.
        if (usedWeight > bag.getCapacity()) {
            return false;
        }

        return true;
    }
};


#endif //INC_01_BNBSOLVER_HPP
