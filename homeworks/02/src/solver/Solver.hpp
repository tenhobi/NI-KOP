#ifndef INC_01_STRATEGY_CPP
#define INC_01_STRATEGY_CPP


#include <SolverResult.hpp>
#include "../Bag.hpp"

class Solver {
public:
    Solver(const Bag &bag) : bag(bag) {}

    virtual SolverResult solve() = 0;

    virtual std::string toString() = 0;

private:
    Bag bag;
};


#endif //INC_01_STRATEGY_CPP
