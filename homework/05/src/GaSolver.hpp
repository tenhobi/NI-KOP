#ifndef INC_01_GASOLVER_HPP
#define INC_01_GASOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include <algorithm>

#include "SAT/Formula.hpp"
#include "Chromosome.hpp"

#define RESET_THRESHOLD 10
#define BEST_THRESHOLD 15

class GaSolver {
private:
    Formula formula;

    // params
    int initialPopulationCount;
    int populationCount;
    int maxGenerationsCount;
    int tournamentSize;
    int elitismSize;
    int mutationProbability;
    int crossoverProbability;

    // other
    int generationsCount = 1;
    std::vector<Chromosome> chromosomes;
    long lastBestFitness = 0;
    int generationsUnchanged = 0;

public:
    GaSolver(Formula formula,
             int initialPopulationCount,
             int populationCount,
             int maxGenerationsCount,
             int tournamentSize,
             bool elitismSize,
             int mutationProbability,
             int crossoverProbability) : formula(std::move(formula)),
                                         initialPopulationCount(initialPopulationCount),
                                         populationCount(populationCount),
                                         maxGenerationsCount(maxGenerationsCount),
                                         tournamentSize(tournamentSize),
                                         elitismSize(elitismSize),
                                         mutationProbability(mutationProbability),
                                         crossoverProbability(crossoverProbability) {}

    Chromosome &solve() {
//        std::cout << "optimal, value, not evaluated" << std::endl;
        solveGa();
        std::sort(this->chromosomes.begin(), this->chromosomes.end());
        std::cout << this->formula.optimalFitness << ", " << this->chromosomes[0].fitness << ", " << this->chromosomes[0].notEvaluated << std::endl;
        return this->chromosomes[0];
    }

protected:
    void solveGa() {

        _initFirstGeneration();
        while (this->generationsCount < this->maxGenerationsCount) {
            _createNextGeneration();
        }
    }

    void _initFirstGeneration() {
        this->chromosomes = {};

        for (int i = 0; i < this->initialPopulationCount - 2; i++) {
            this->chromosomes.emplace_back(this->formula);
        }

        // All false and all true.
        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), false));
        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), true));
    }

    void _createNextGeneration() {
        this->generationsCount++;

        std::sort(this->chromosomes.begin(), this->chromosomes.end());

        std::cout << this->formula.optimalFitness << ", " << this->chromosomes[0].fitness << ", " << this->chromosomes[0].notEvaluated << std::endl;

        if (this->lastBestFitness == this->chromosomes[0].fitness) {
            this->generationsUnchanged++;
        } else {
            this->lastBestFitness = this->chromosomes[0].fitness;
            this->generationsUnchanged = 0;
        }

        // Resetting if stuck mechanism.
        if (this->generationsUnchanged == RESET_THRESHOLD && this->chromosomes[0].notEvaluated > 0) {
            this->generationsUnchanged = 0;
            this->_initFirstGeneration();
            return;
        }

        // Cannot find better solution.
        if (this->generationsUnchanged == BEST_THRESHOLD && this->chromosomes[0].notEvaluated == 0) {
            this->generationsUnchanged = 0;

            std::vector<Chromosome> thisGeneration;
            thisGeneration.push_back(this->chromosomes[0]);
            for (int i = 1; i < this->populationCount; i++) {
                thisGeneration.emplace_back(this->formula);
            }
            this->chromosomes = thisGeneration;

            return;
        }

        // START NEW GENERATION:
        // ---------------------
        std::vector<Chromosome> thisGeneration;

        // Elitism
        thisGeneration.reserve(this->elitismSize);
        for (int i = 0; i < this->elitismSize; i++) {
            thisGeneration.push_back(this->chromosomes[i]);
        }

        // Selection
        while ((int) thisGeneration.size() < this->populationCount) {
            this->normalGA(thisGeneration);
        }

        // Replace last generation.
        this->chromosomes = thisGeneration;
    }

    void normalGA(std::vector<Chromosome> &thisGeneration) {
        Chromosome parent1 = this->select();
        Chromosome parent2 = this->select();
        Chromosome child1 = parent1;
        Chromosome child2 = parent2;

        // Crossover
        if (rand() % 100 < this->crossoverProbability) {
            std::tie(child1, child2) = Chromosome::cross(parent1, parent2);
        }

        // Mutation for child 1.
        if (rand() % 100 < this->mutationProbability) {
            child1 = child1.mutate();
        }

        // Mutation for child 2
        if (rand() % 100 < this->mutationProbability) {
            child2 = child2.mutate();
        }

        thisGeneration.push_back(child1);
        thisGeneration.push_back(child2);
    }

    void GAwithDeterministicCrowding(std::vector<Chromosome> &thisGeneration) {
        Chromosome parent1 = this->select();
        Chromosome parent2 = this->select();
        Chromosome child1, child2;
        std::tie(child1, child2) = Chromosome::cross(parent1, parent2);

        // Mutation for child 1
        if (rand() % 100 < this->mutationProbability) {
            child1 = child1.mutate();
        }

        // Mutation for child 2
        if (rand() % 100 < this->mutationProbability) {
            child2 = child2.mutate();
        }

        if (Chromosome::distance(parent1, child1) + Chromosome::distance(parent2, child2) <=
            Chromosome::distance(parent1, child2) + Chromosome::distance(parent2, child1)) {
            if (child1.fitness > parent1.fitness) {
                thisGeneration.push_back(child1);
            } else {
                thisGeneration.push_back(parent1);
            }
            if (child2.fitness > parent2.fitness) {
                thisGeneration.push_back(child2);
            } else {
                thisGeneration.push_back(parent2);
            }
        } else {
            if (child1.fitness > parent2.fitness) {
                thisGeneration.push_back(child1);
            } else {
                thisGeneration.push_back(parent2);
            }
            if (child2.fitness > parent1.fitness) {
                thisGeneration.push_back(child2);
            } else {
                thisGeneration.push_back(parent1);
            }
        }
    }

    // Selection using tournament.
    Chromosome select() {
        return this->selectTournament();
    }

    // Selection algorithm using only random method.
    Chromosome selectRandom() {
        return this->chromosomes[rand() % (int) this->chromosomes.size()];
    }

    // Selection algorithm using tournament.
    Chromosome selectTournament() {
        std::vector<Chromosome> tournament;

        tournament.reserve(this->tournamentSize);
        for (int i = 0; i < this->tournamentSize; i++) {
            tournament.push_back(this->chromosomes[rand() % (int) this->chromosomes.size()]);
        }

        std::sort(tournament.begin(), tournament.end());

        return tournament[0];
    }
};

#endif //INC_01_GASOLVER_HPP
