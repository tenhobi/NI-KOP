#ifndef INC_01_SOLVERFACTORY_HPP
#define INC_01_SOLVERFACTORY_HPP


#include <string>
#include "Solver.hpp"
#include "BfSolver.hpp"
#include "BnbSolver.hpp"

class SolverFactory {
public:
    static Solver fromString(std::string methodString, Bag bag) {
        if (methodString == "bf") {
            return BfSolver(bag);
        } else if (methodString == "bnb") {
            return BnbSolver(bag);
        }

        return nullptr;
    }
};


#endif //INC_01_SOLVERFACTORY_HPP
