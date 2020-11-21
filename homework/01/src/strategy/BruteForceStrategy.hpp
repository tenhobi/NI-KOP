//
// Created by the on 10/10/2020.
//

#ifndef INC_01_BRUTEFORCESTRATEGY_HPP
#define INC_01_BRUTEFORCESTRATEGY_HPP


#include "Strategy.hpp"

class BruteForceStrategy : public Strategy {
public:
    bool shouldContinue(Bag bag,
                        Item item,
                        unsigned long usedWeight,
                        unsigned long collectedCost,
                        unsigned long estimate) const override {
        return true;
    }
};


#endif //INC_01_BRUTEFORCESTRATEGY_HPP
