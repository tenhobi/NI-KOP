#ifndef INC_05_FORMULA_HPP
#define INC_05_FORMULA_HPP


#include <utility>

#include "Clause.hpp"

class Formula {
public:
    std::string id;
    long optimalFitness;
    std::vector<int> weights;
    std::vector<Clause> clauses;

    Formula() = default;

    explicit Formula(std::string id,
                     long optimalFitness,
                     std::vector<int> weights,
                     std::vector<Clause> clauses) : id(std::move(id)),
                                                    optimalFitness(optimalFitness),
                                                    weights(std::move(weights)),
                                                    clauses(std::move(clauses)) {}

    std::pair<bool, int> evaluate(const std::vector<bool> &variables) const {
        bool valueFlag = true;
        int evaluatedClausesCount = 0;

        for (Clause clause: this->clauses) {
            bool value = clause.evaluate(variables);

            if (value) {
                evaluatedClausesCount++;
            }
            valueFlag &= value;
        }

        return {valueFlag, evaluatedClausesCount};
    }

    void toString() const {
        std::cout << "id: " << id << ", weights:";

        for (auto weight: this->weights) {
            std::cout << " " << weight;
        }

        std::cout << std::endl;

        for (const auto &clause: this->clauses) {
            clause.toString();
        }
    }
};


#endif //INC_05_FORMULA_HPP
