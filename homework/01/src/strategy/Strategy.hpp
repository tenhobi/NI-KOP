//
// Created by the on 10/10/2020.
//

#ifndef INC_01_STRATEGY_CPP
#define INC_01_STRATEGY_CPP


#include "../Bag.hpp"

class Strategy {
public:
    virtual void initData(Bag bag) const {}

    virtual bool shouldContinue(Bag bag,
                                Item item,
                                unsigned long usedWeight,
                                unsigned long collectedCost,
                                unsigned long estimate) const { return true; }
};


#endif //INC_01_STRATEGY_CPP
