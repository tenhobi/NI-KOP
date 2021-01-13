#ifndef INC_05_FORMULA_HPP
#define INC_05_FORMULA_HPP


#include <utility>

#include "Clause.hpp"

class Formula {
public:
    std::string id;
    std::vector<int> weights;
    std::vector<Clause> clauses;

    Formula() = default;

    explicit Formula(std::string id,
                     std::vector<int> weights) : id(std::move(id)),
                                                 weights(std::move(weights)) {}

    std::pair<bool, int> evaluate(const std::vector<bool> &variables) const {
        int evaluatedClausesCount = 0;
        bool valueFlag = true;

        for (Clause clause: this->clauses) {
            bool value = clause.evaluate(variables);

            if (value) {
                evaluatedClausesCount++;
            }
            valueFlag &= value;
        }

        return {valueFlag, evaluatedClausesCount};
    }
};


#endif //INC_05_FORMULA_HPP
