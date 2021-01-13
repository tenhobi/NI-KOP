#ifndef INC_01_CHROMOSOME_HPP
#define INC_01_CHROMOSOME_HPP


#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "SAT/Formula.hpp"

#define FITNESS_PENALTY -100
#define INITIAL_ITEM_PROBABILITY 40 // percent

class Chromosome {
private:
    Formula formula;
    std::vector<bool> genes;
    unsigned long fitness = 0;

public:
    Chromosome() = default;

    // For initial population, generate chromosome.
    explicit Chromosome(Formula &formula) : formula(formula) {
        this->genes = std::vector<bool>();

        for (int i = 0; i < (int) this->formula.weights.size(); i++) {
            int shouldAdd = rand() % 100;
            this->genes.push_back(shouldAdd < INITIAL_ITEM_PROBABILITY);
        }

        this->fitness = calculateFitness();
    }

    // For mutations and crossing.
    Chromosome(Formula &formula, std::vector<bool> genes) :
            formula(formula),
            genes(std::move(genes)) {
        this->fitness = calculateFitness();
    }

    Chromosome mutate() {
        int geneToMutate = rand() % genes.size(); // 0 .. size-1

        std::vector<bool> tmpGenes = genes;

        tmpGenes[geneToMutate] = 1 - genes[geneToMutate];

        return Chromosome(formula, tmpGenes);
    }

    Chromosome cross(Chromosome &other) {
        int crossPoint = rand() % genes.size(); // 0 .. size-1

        std::vector<bool> tmpGenes = genes;

        // Copy second part (other) chromosome.
        for (int i = crossPoint; i < (int) tmpGenes.size(); i++) {
            tmpGenes[i] = other.genes[i];
        }

        return Chromosome(formula, tmpGenes);
    }

    unsigned long calculateFitness() {
        unsigned long sumWeight = 0;

        auto pair = this->formula.evaluate(this->genes);
        bool evaluated = pair.first;
        int evaluatedClausesCount = pair.second;

        // Fitness is sum weight of used genes.
        if (evaluated) {
            for (int i = 0; i < (int) this->genes.size(); i++) {
                if (this->genes[i]) {
                    sumWeight += this->formula.weights[i];
                }
            }

            return sumWeight;
        }

        // Else fitness is number of not evaluated clauses * FITNESS_PENALTY.
        return (this->formula.clauses.size() - evaluatedClausesCount) * FITNESS_PENALTY;
    }

    bool operator<(const Chromosome &chromosome) const {
        return this->fitness < chromosome.fitness;
    }
};


#endif //INC_01_CHROMOSOME_HPP
