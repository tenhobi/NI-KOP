#ifndef INC_05_LOADER_HPP
#define INC_05_LOADER_HPP

#include <string>
#include <utility>

#include "SAT/Formula.hpp"

class Loader {
private:
    std::string fileName;

public:
    explicit Loader(std::string fileName) : fileName(std::move(fileName)) {}

public:

//    c This Formular is generated by mcnf
//    c
//    c    horn? no
//    c    forced? no
//    c    mixed sat? no
//    c    clause length = 3
//    c
//    p mwcnf 20 79
//    c SAT instance uf20-78/uf20-01.cnf
//    w 491 260 355 449 1 384 282 239 392 651 358 562 100 455 16 51 683 50 332 409 0
//    c range 100 1500 straight
//    4 -18 19 0
//    3 18 -5 0

    Formula loadFormula() {
        std::ifstream file(this->fileName);

        if (!file.is_open()) {
            std::cout << "Error: Couldn't open the input file." << std::endl;
            exit(2);
        }

        bool shouldBreak = false;
        std::string id;
        int variablesCount;
        int clausesCount;
        std::vector<int> variablesWeights;

        // Load id, variablesCount, clausesCount, weights vector
        std::string line;
        int lastPos = file.tellg();
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            char lineType;
            lineStream >> std::noskipws >> lineType; // Don't forget to turn on skipping.

            switch (lineType) {
                case ' ':
                    shouldBreak = true;
                    file.seekg(lastPos);
                    break;
                case 'c':
                    break;
                case 'p':
                    lineStream >> std::skipws >> id >> variablesCount >> clausesCount;
                    break;
                case 'w':
                    lineStream >> std::skipws;
                    int value;
                    for (int i = 0; i < variablesCount; i++) {
                        lineStream >> value;
                        variablesWeights.push_back(value);
                    }
                    break;
                default:
                    shouldBreak = true;
                    break;
            }

            if (shouldBreak) break;

            lastPos = file.tellg();
        }

        std::vector<Clause> clauses;
        // Load clauses
        for (int i = 1; i < clausesCount; i++) {
            int one, two, three, nothing;
            file >> one >> two >> three >> nothing;
            std::vector<int> tmp = {one, two, three};
            clauses.emplace_back(tmp);
        }

        file.close();

        // TODO: read file to get optimal solution
        return Formula(id, variablesWeights, clauses);
    }
};


#endif //INC_05_LOADER_HPP
