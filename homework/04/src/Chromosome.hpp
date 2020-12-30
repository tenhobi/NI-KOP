#ifndef INC_01_CHROMOSOME_HPP
#define INC_01_CHROMOSOME_HPP


#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Bag.hpp"

#define FITNESS_PENALTY 100000
#define INITIAL_ITEM_PROBABILITY 30 // percent

class Chromosome {
public:
    // For initial population.
    Chromosome(Bag &bag) : bag(bag) {
        this->genes = std::vector<int>();

        // Use some configuration from average bag's item cost.
        unsigned long averageCost = 0;
        for (auto&& item: this->bag.items) {
            averageCost += item.getCost() / this->bag.items.size();
        }

        // Add only items better than average with some probability.
        for (int i = 0; i < (int) this->bag.items.size(); i++) {
            int shouldAdd = rand() % 100;

            if (this->bag.items[i].getCost() >= averageCost && shouldAdd >= INITIAL_ITEM_PROBABILITY) {
                this->genes.push_back(1);
            } else {
                this->genes.push_back(0);
            }
        }

        calculateFitness();
    }

    // For mutations and crossing.
    Chromosome(Bag &bag, std::vector<int> genes) :
            bag(bag),
            genes(std::move(genes)) {
        calculateFitness();
    }

    Bag bag;
    std::vector<int> genes;
    unsigned long fitness;

    Chromosome *mutate() {
        int geneToMutate = rand() % genes.size(); // 0 .. size-1
        printf("random mutate: %d\n", geneToMutate);

        std::vector<int> tmpGenes = genes; // TODO ?

        tmpGenes[geneToMutate] = 1 - genes[geneToMutate];

        return new Chromosome(bag, tmpGenes);
    }

    Chromosome *cross(Chromosome *other) {
        int crossPoint = rand() % genes.size(); // 0 .. size-1
        printf("random cross point: %d\n", crossPoint);

        std::vector<int> tmpGenes = genes; // Copy first part (this) chromosome. TODO ?

        // Copy second part (other) chromosome.
        for (int i = crossPoint; i < (int) tmpGenes.size(); i++) {
            tmpGenes[i] = other->genes[i];
        }

        return new Chromosome(bag, tmpGenes);
    }

    void calculateFitness() {
        unsigned long sumWeight = 0;
        unsigned long sumCost = 0;

        for (int i = 0; i < (int) this->genes.size(); i++) {
            if (this->genes[i] != 0) {
                auto& item = this->bag.items[i];
                sumWeight += item.getWeight();
                sumCost += item.getCost();
            }
        }

        this->fitness = sumCost;

        if (sumWeight > this->bag.capacity) {
            this->fitness -= FITNESS_PENALTY;
        }
    }
};


#endif //INC_01_CHROMOSOME_HPP
