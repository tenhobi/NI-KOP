#ifndef INC_01_SOLVERFACTORY_HPP
#define INC_01_SOLVERFACTORY_HPP


#include <string>
#include "Solver.hpp"
#include "BfSolver.hpp"
#include "BnbSolver.hpp"
#include "DynSolver.hpp"
#include "GreedySolver.hpp"

class SolverFactory {
public:
    static Solver *fromString(const std::string &methodString, Bag bag) {
        if (methodString == "bf") {
            return new BfSolver(bag);
        } else if (methodString == "bnb") {
            return new BnbSolver(bag);
        } else if (methodString == "dyn") {
            return new DynSolver(bag);
        } else if (methodString == "greedy") {
            return new GreedySolver(bag, false);
        } else if (methodString == "greedyMod") {
            return new GreedySolver(bag, true);
        }

        return nullptr;
    }
};


#endif //INC_01_SOLVERFACTORY_HPP
