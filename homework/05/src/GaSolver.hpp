#ifndef INC_01_GASOLVER_HPP
#define INC_01_GASOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include <algorithm>

#include "SAT/Formula.hpp"
#include "Chromosome.hpp"

//struct ChromosomeCompare {
//    bool operator()(const Chromosome *l, const Chromosome *r) {
//        return l->fitness > r->fitness;
//    }
//};

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

        while (this->generationsCount <= this->maxGenerationsCount) {
            _createNextGeneration();
        }


//        std::cout << this->lastMaxCost << std::endl;
    }

    void _initFirstGeneration() {
        for (int i = 0; i < this->initialPopulationCount; i++) {
            this->chromosomes.emplace_back(this->formula);
        }

        // All false and all true.
        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), false));
        this->chromosomes.emplace_back(this->formula, std::vector<bool>(this->formula.weights.size(), true));
    }

    void _createNextGeneration() {
        this->generationsCount++;
        std::sort(this->chromosomes.begin(), this->chromosomes.end()); // TODO
        std::vector<Chromosome> thisGeneration;

        // Elitism
        for (int i = 0; i < this->elitismSize; i++) {
            thisGeneration.push_back(this->chromosomes[i]);
        }

        // Selection
        for (int i = this->elitismSize; i < this->populationCount; i++) {
            Chromosome next;

            // Crossover
            if (rand() % 100 < this->crossoverProbability) {
                next = this->select().cross(this->select());
            } else {
                next = this->select();
            }

            // Mutation
            if (rand() % 100 < this->mutationProbability) {
                next.mutate();
            }

            thisGeneration.push_back(next);
        }

        // Replace last generation.
        this->chromosomes = thisGeneration;
    }

    // Selection using tournament.
    Chromosome select() {
        std::vector<Chromosome> tournament;

        for (int i = 0; i < this->tournamentSize; i++) {
            tournament.push_back(this->chromosomes[rand() % (int) this->chromosomes.size()]);
        }

        std::sort(tournament.begin(), tournament.end()); // TODO

        return tournament[0];
    }
};

#endif //INC_01_GASOLVER_HPP
