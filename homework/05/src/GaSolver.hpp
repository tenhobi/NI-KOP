#ifndef INC_01_GASOLVER_HPP
#define INC_01_GASOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include <algorithm>

#include "SAT/Formula.hpp"
#include "Chromosome.hpp"

#define RESET_THRESHOLD 30
#define BEST_THRESHOLD 30

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
    int generationsCount = 0;
    std::vector<Chromosome> chromosomes;
    long lastBestFitness = 0;
    int generationsUnchanged = 0;
    bool cannotFindBetter = false;

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
        solveGa();

        return this->chromosomes[0];
    }

protected:
    void solveGa() {
        // TODO
        // - přidat počáteční chromozomy
        _initFirstGeneration();
        // --- for 1..x:

        while (!cannotFindBetter && this->generationsCount <= this->maxGenerationsCount) {
            _createNextGeneration();
        }


//        std::cout << this->lastMaxCost << std::endl;
    }

    void _initFirstGeneration() {
        this->chromosomes = {};

        for (int i = 0; i < this->initialPopulationCount; i++) {
            this->chromosomes.emplace_back(this->formula);
        }

//         All false and all true.
//        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), false));
//        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), true));
    }

    void _createNextGeneration() {
        this->generationsCount++;
        if (this->generationsCount % 10 == 0) {
            std::cout << "Generation " << this->generationsCount << std::endl;
        }

        std::sort(this->chromosomes.begin(), this->chromosomes.end());

        if (this->lastBestFitness == this->chromosomes[0].fitness) {
            this->generationsUnchanged++;
        } else {
            this->lastBestFitness = this->chromosomes[0].fitness;
            this->generationsUnchanged = 0;
        }

        // Resetting if stuck mechanism.
        if (this->generationsUnchanged == RESET_THRESHOLD && this->chromosomes[0].notEvaluated > 0) {
            std::cout << "RESETTING" << std::endl;
            this->_initFirstGeneration();
            std::sort(this->chromosomes.begin(), this->chromosomes.end());
        }

        // Cannot find better solution.
        if (this->generationsUnchanged == BEST_THRESHOLD && this->chromosomes[0].notEvaluated == 0) {
            std::cout << "BEST I CAN FOUND" << std::endl;
            this->cannotFindBetter = true;
            return;
        }

        std::cout << this->chromosomes[0].fitness << ", " << this->chromosomes[0].notEvaluated << ", "
                  << this->chromosomes[0].weight << std::endl;

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
//            this->GAwithDeterministicCrowding(thisGeneration);
        }

        // Replace last generation.
        this->chromosomes = thisGeneration;
    }

    void normalGA(std::vector<Chromosome> &thisGeneration) {
        Chromosome next = this->select();

        // Crossover
        if (rand() % 100 < this->crossoverProbability) {
            Chromosome parent2 = this->select();
            next = next.cross(parent2);
        }

        // Mutation
        if (rand() % 100 < this->mutationProbability) {
            next = next.mutate();
        }

        thisGeneration.push_back(next);
    }

    void GAwithDeterministicCrowding(std::vector<Chromosome> &thisGeneration) {
        Chromosome parent1 = this->select();
        Chromosome parent2 = this->select();
        Chromosome child1 = parent1.cross(parent2);
        Chromosome child2 = parent1.cross(parent1);

        // Mutation for child 1
        if (rand() % 100 < this->mutationProbability) {
            child1 = child1.mutate();
        }

        // Mutation for child 2
        if (rand() % 100 < this->mutationProbability) {
            child2 = child2.mutate();
        }

        if (distance(parent1, child1) + distance(parent2, child2) <=
            distance(parent1, child2) + distance(parent2, child1)) {
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

    int distance(Chromosome &first, Chromosome &second) {
        return first.distance(second);
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

        for (int i = 0; i < this->tournamentSize; i++) {
            tournament.push_back(this->chromosomes[rand() % (int) this->chromosomes.size()]);
        }

        std::sort(tournament.begin(), tournament.end());

        return tournament[0];
    }
};

#endif //INC_01_GASOLVER_HPP
