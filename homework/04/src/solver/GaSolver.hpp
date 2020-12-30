#ifndef INC_01_GASOLVER_HPP
#define INC_01_GASOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include <algorithm>

#include "../Chromosome.hpp"
#include "Solver.hpp"

#define POPULATION_COUNT 200
#define GENERATIONS_COUNT_MAX 35
#define GENERATIONS_UNCHANGED 15
#define PROBABILITY_MUTATION 10 // percent
#define PROBABILITY_CROSS 25 // percent

struct ChromosomeCompare {
    bool operator()(const Chromosome *l, const Chromosome *r) {
        return l->fitness > r->fitness;
    }
};

class GaSolver : public Solver {
public:
    explicit GaSolver(Bag &bag) : Solver(bag), generationCount(0), lastMaxCost(0),
                                  generationsSinceMaxFitnessChanged(0) {}

    void solve() override {
        solveGa();
    }

    void print() override {
        // TODO
//        std::cout << bag.id << " " << bag.n << " " << resultCost;
//
//        for (auto &&item : itemsFlag) {
//            std::cout << " " << (item ? "1" : "0");
//        }
//
//        std::cout << std::endl;
    }

protected:
    std::vector<Chromosome *> chromosomes;
    int generationCount;
    unsigned long lastMaxCost;
    int generationsSinceMaxFitnessChanged;

    void solveGa() {
        // TODO
        // - přidat počáteční chromozomy
        _initFirstGeneration();
        // --- for 1..x:

        while (this->generationCount <= GENERATIONS_COUNT_MAX) {
            if (this->lastMaxCost != 0 && this->generationsSinceMaxFitnessChanged > GENERATIONS_UNCHANGED) {
                break;
            }

            _createNextGeneration();
        }


        std::cout << this->lastMaxCost << std::endl;
    }

    void _initFirstGeneration() {
        for (int i = 0; i < POPULATION_COUNT; i++) {
            this->chromosomes.push_back(new Chromosome(bag));
        }
        this->chromosomes.push_back(new Chromosome(bag, std::vector<int>(bag.items.size(), 0)));
        this->chromosomes.push_back(new Chromosome(bag, std::vector<int>(bag.items.size(), 1)));

        std::sort(this->chromosomes.begin(), this->chromosomes.end(), ChromosomeCompare());

//        for (auto & chromosome : this->chromosomes) {
//            toText(chromosome);
//        }
    }

    void _createNextGeneration() {
        this->generationCount++;
        //std::cout << "generation " << this->generationCount << std::endl;

        if (this->lastMaxCost == this->chromosomes[0]->fitness) {
            this->generationsSinceMaxFitnessChanged++;
        } else {
            this->generationsSinceMaxFitnessChanged = 1;
        }

        this->lastMaxCost = this->chromosomes[0]->fitness;
        //std::cout << this->lastMaxCost << std::endl;

        // last generation
        std::vector<Chromosome *> thisGeneration = this->chromosomes;

        // - mutace, křížení
        for (auto &chromosome : this->chromosomes) {
            int shouldCross = rand() % 100;
            if (shouldCross <= PROBABILITY_CROSS) {
                for (auto &secondChromosome : this->chromosomes) {
                    thisGeneration.push_back(chromosome->cross(secondChromosome));
                }
            }

            int shouldMute = rand() % 100;
            if (shouldMute <= PROBABILITY_MUTATION) {
                thisGeneration.push_back(chromosome->mutate());
            }
        }

        // - sort + vyhodit nevhodné
        std::sort(thisGeneration.begin(), thisGeneration.end(), ChromosomeCompare());
//        std::cout << thisGeneration.size() << std::endl;
//        std::cout << generationsSinceMaxFitnessChanged << std::endl;
        for (int i = POPULATION_COUNT; i < (int) thisGeneration.size(); i++) {
            delete thisGeneration[i];
        }
        thisGeneration.resize(POPULATION_COUNT);
        this->chromosomes = thisGeneration;
    }

    // TODO: remove
    static void toText(Chromosome *chromosome) {
        std::cout << chromosome->fitness << " = ";

        for (auto &&item : chromosome->genes) {
            std::cout << item;
        }

        std::cout << std::endl;
    }
};

#endif //INC_01_GASOLVER_HPP
