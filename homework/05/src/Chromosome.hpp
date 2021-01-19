#ifndef INC_01_CHROMOSOME_HPP
#define INC_01_CHROMOSOME_HPP


#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "SAT/Formula.hpp"

#define FITNESS_PENALTY -10
#define INITIAL_ITEM_PROBABILITY 40 // percent

class Chromosome {
private:
    Formula formula;
    std::vector<bool> genes;
    unsigned long fitness = 0;

public:
    Chromosome() = default;

    // For initial population, generate chromosome.
    explicit Chromosome(Formula formula) : formula(std::move(formula)) {
        this->genes = std::vector<bool>();

        for (int i = 0; i < (int) this->formula.weights.size(); i++) {
            int shouldAdd = rand() % 100;
            this->genes.push_back(shouldAdd < INITIAL_ITEM_PROBABILITY);
        }

        this->fitness = calculateFitness();
    }

    // For mutations and crossing.
    Chromosome(Formula formula, std::vector<bool> genes) :
            formula(std::move(formula)),
            genes(std::move(genes)) {
        this->fitness = calculateFitness();
    }

    Chromosome mutate() {
        int geneToMutate = rand() % genes.size(); // 0 .. size-1

        std::vector<bool> tmpGenes = genes;

        tmpGenes[geneToMutate] = 1 - genes[geneToMutate];

        return Chromosome(formula, tmpGenes);
    }

    Chromosome cross(const Chromosome &other) const {
        int crossPoint = rand() % genes.size(); // 0 .. size-1

        std::vector<bool> tmpGenes = genes;

        // Copy second part (other) chromosome.
        for (int i = crossPoint; i < (int) tmpGenes.size(); i++) {
            tmpGenes[i] = other.genes[i];
        }

        return Chromosome(formula, tmpGenes);
    }

    long calculateFitness() {
        bool evaluated;
        int evaluatedClausesCount;
        std::tie (evaluated, evaluatedClausesCount) = this->formula.evaluate(this->genes);

        // Fitness is sum weight of used genes.
        if (evaluated) {
            long weightSum = 0;
            for (int i = 0; i < (int) this->formula.weights.size(); i++) {
                if (this->genes[i]) {
                    weightSum += this->formula.weights[i];
                }
            }
            return weightSum;
        }

        // Else fitness is number of not evaluated clauses * FITNESS_PENALTY.
        return ((int) this->formula.clauses.size() - evaluatedClausesCount) * FITNESS_PENALTY;
    }

    bool operator<(const Chromosome &chromosome) const {
        return this->fitness < chromosome.fitness;
    }

    void toString() const {
        for (auto gene: this->genes) {
            std::cout << gene << " ";
        }

        std::cout << std::endl;
    }
};


#endif //INC_01_CHROMOSOME_HPP
