#ifndef INC_01_CHROMOSOME_HPP
#define INC_01_CHROMOSOME_HPP


#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "SAT/Formula.hpp"

#define FITNESS_PENALTY 1500

class Chromosome {
private:
    Formula formula;
    std::vector<bool> genes;

public:
    long fitness = 0;
    long weight = 0;
    long notEvaluated = 0;

    Chromosome() = default;

    // For initial population, generate chromosome.
    explicit Chromosome(Formula formula) : formula(std::move(formula)) {
        this->genes = std::vector<bool>();

        for (int i = 0; i < (int) this->formula.weights.size(); i++) {
            int shouldAdd = rand() % 2;
            this->genes.push_back(shouldAdd == 1);
        }

        this->weight = calculateWeight();
        this->fitness = calculateFitness();
    }

    // For mutations and crossing.
    Chromosome(Formula formula, std::vector<bool> genes) :
            formula(std::move(formula)),
            genes(std::move(genes)) {
        this->weight = calculateWeight();
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

    int distance(const Chromosome &other) const {
        int sum = 0;
        for (int i = 0; i < (int) this->genes.size(); i++) {
            sum += this->genes[i] == other.genes[i] ? 0 : 1;
        }
        return sum;
    }

    bool operator<(const Chromosome &chromosome) const {
        return this->fitness > chromosome.fitness;
    }

    void toString() const {
        std::cout << this->fitness << " = ";

        for (auto gene: this->genes) {
            std::cout << gene << " ";
        }

        std::cout << std::endl;
    }

private:

    long calculateWeight() {
        long weightSum = 0;
        for (int i = 0; i < (int) this->formula.weights.size(); i++) {
            if (this->genes[i]) {
                weightSum += this->formula.weights[i];
            }
        }

        return weightSum;
    }

    long calculateFitness() {
        bool evaluated;
        int evaluatedClausesCount;
        std::tie(evaluated, evaluatedClausesCount) = this->formula.evaluate(this->genes);

        this->notEvaluated = (int) this->formula.clauses.size() - evaluatedClausesCount;
        return this->weight - ((int) this->formula.clauses.size() - evaluatedClausesCount) * FITNESS_PENALTY;
    }
};

#endif //INC_01_CHROMOSOME_HPP
