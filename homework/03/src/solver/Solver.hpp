#ifndef INC_01_STRATEGY_CPP
#define INC_01_STRATEGY_CPP


#include "../Bag.hpp"

class Solver {
public:
    explicit Solver(Bag &bag) : bag(bag) {}

    virtual void solve() = 0;

    virtual void print() = 0;

protected:
    Bag bag;

    unsigned long calculateBestBagEstimate() {
        unsigned long estimate = 0;

        for (auto item: bag.items) {
            estimate += item.getCost();
        }

        return estimate;
    }
};


#endif //INC_01_STRATEGY_CPP
