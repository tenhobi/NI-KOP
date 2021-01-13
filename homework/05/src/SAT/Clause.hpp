#ifndef INC_05_CLAUSE_HPP
#define INC_05_CLAUSE_HPP


class Clause {
public:
    std::vector<std::pair<int, bool>> literalsList{}; // literal = variable id, negation

    explicit Clause(std::vector<int> variables) {
        for (int variable : variables) {
            this->literalsList.emplace_back(abs(variable), variable < 0);
        }
    }

    bool evaluate(const std::vector<bool> &variables) {
        for (auto literalPair: this->literalsList) {
            // Variable presence is not equal to literal's negation flag:
            // 1 with negation (1) => 0
            // 1 with not negation (0) => 1
            // 0 with negation (1) => 1
            // 0 with not negation (0) => 0
            if (variables[literalPair.first] != literalPair.second) {
                return true;
            }
        }

        return false;
    }
};


#endif //INC_05_CLAUSE_HPP
