#ifndef INC_01_CHROMOSOME_HPP
#define INC_01_CHROMOSOME_HPP


#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "SAT/Formula.hpp"

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

    static std::pair<Chromosome, Chromosome> cross(const Chromosome &first, const Chromosome &second) {
        return crossUniform(first, second);
    }

    static std::pair<Chromosome, Chromosome> crossBoth(const Chromosome &first, const Chromosome &second) {
        if (rand() % 2 == 0) {
            return Chromosome::crossOnePoint(first, second);
        } else {
            return Chromosome::crossUniform(first, second);
        }
    }

    static std::pair<Chromosome, Chromosome> crossUniform(const Chromosome &first, const Chromosome &second) {
        std::vector<bool> uniformArray;

        uniformArray.reserve((int) first.genes.size());
        for (int i = 0; i < (int) first.genes.size(); i++) {
            uniformArray.push_back(rand() % 2 == 0);
        }

        std::vector<bool> tmpGenes1, tmpGenes2;

        // Build children.
        for (int i = 0; i < (int) uniformArray.size(); i++) {
            tmpGenes1.push_back(uniformArray[i] ? first.genes[i] : second.genes[i]);
            tmpGenes2.push_back(uniformArray[i] ? second.genes[i] : first.genes[i]);
        }

        return {Chromosome(first.formula, tmpGenes1), Chromosome(first.formula, tmpGenes2)};
    }

    static std::pair<Chromosome, Chromosome> crossOnePoint(const Chromosome &first, const Chromosome &second) {
        int crossPoint = rand() % first.genes.size(); // 0 .. size-1

        std::vector<bool> tmpGenes1 = first.genes; // first genes | second genes
        std::vector<bool> tmpGenes2 = second.genes; // second genes | first genes

        // Build first child.
        for (int i = crossPoint; i < (int) tmpGenes1.size(); i++) {
            tmpGenes1[i] = second.genes[i];
        }

        // Build second child.
        for (int i = 0; i < crossPoint; i++) {
            tmpGenes2[i] = first.genes[i];
        }

        return {Chromosome(first.formula, tmpGenes1), Chromosome(first.formula, tmpGenes2)};
    }

    static int distance(const Chromosome &first, const Chromosome &second) {
        int sum = 0;
        for (int i = 0; i < (int) first.genes.size(); i++) {
            sum += first.genes[i] == second.genes[i] ? 0 : 1;
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
        if (this->notEvaluated > 0) {
            return -this->notEvaluated;
        }
        return this->weight;
    }
};

#endif //INC_01_CHROMOSOME_HPP
