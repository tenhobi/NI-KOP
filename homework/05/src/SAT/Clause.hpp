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

    // uf20-01 6403 1 2 3 4 -5 6 7 8 9 10 11 12 -13 14 -15 16 17 18 19 20 0
    bool evaluate(const std::vector<bool> &variables) {
        for (auto literalPair: this->literalsList) {
            // Variable presence is not equal to literal's negation flag:
            // 1 with negation (1) => 0
            // 1 with not negation (0) => 1
            // 0 with negation (1) => 1
            // 0 with not negation (0) => 0
            if (variables[literalPair.first - 1] != literalPair.second) {
                return true;
            }
        }

        return false;
    }

    void toString() const {
        for (auto pair: this->literalsList) {
            if (pair.second) {
                std::cout << '-';
            }
            std::cout << pair.first << " ";
        }

        std::cout << std::endl;
    }
};


#endif //INC_05_CLAUSE_HPP
