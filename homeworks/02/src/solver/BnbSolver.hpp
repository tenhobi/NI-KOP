#ifndef INC_01_BNBSOLVER_HPP
#define INC_01_BNBSOLVER_HPP


#include "Solver.hpp"

class BnbSolver : public Solver {
public:
    explicit BnbSolver(Bag &bag) : Solver(bag) {}

    void solve() override {}

    std::string toString() override {
        return "bnb solver";
    }
private:

};


#endif //INC_01_BNBSOLVER_HPP
