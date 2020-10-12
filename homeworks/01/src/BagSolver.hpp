//
// Created by the on 10/11/2020.
//

#ifndef INC_01_BAGSOLVER_HPP
#define INC_01_BAGSOLVER_HPP


#include "strategy/Strategy.hpp"
#include <utility>

class BagSolver {
public:
    void solveBag() {
        if (alreadyUsed) return;
        alreadyUsed = true;

        unsigned long estimate = calculateEstimateForBag();
        strategy->initData(bag);

        processRecursion(-1, 0, 0, estimate);
    }

    BagSolver(Strategy *strategy, Bag bag) : strategy(strategy), bag(std::move(bag)),
                                             configurationFounded(false),
                                             visitedNodes(0),
                                             alreadyUsed(false) {}

    bool isConfigurationFounded() const {
        return configurationFounded;
    }

    unsigned long getVisitedNodes() const {
        return visitedNodes;
    }

private:
    Strategy *strategy;
    Bag bag;
    bool configurationFounded;
    unsigned long visitedNodes;
    bool alreadyUsed;

    unsigned long calculateEstimateForBag() {
        unsigned long estimate = 0;

        for (auto item: bag.getItems()) {
            estimate += item.getCost();
        }

        return estimate;
    }

    /**
     * Recursion alg. to process the bag.
     *
     * @param level index of the processing item
     * @param weight collected weight
     * @param cost collected cost
     * @param costEstimate estimate of cost that can be still used
     */
    void processRecursion(long level, unsigned long weight, unsigned long cost, unsigned long costEstimate) {
        if (configurationFounded) return;

        Item currentItem = Item(0, 0);

        if (level != -1) {
            currentItem = bag.getItems().at(level);
        }

        visitedNodes++;

        if (!strategy->shouldContinue(bag, currentItem, weight, cost, costEstimate)) {
            return;
        }

        // Check last item
        if ((unsigned long) (level) == (bag.getItems().size() - 1)) {
            bool with = ((weight + bag.getItems().at(level).getWeight()) <= bag.getCapacity()) &&
                        ((cost + bag.getItems().at(level).getCost()) >= bag.getMinimalCost());
            bool without = (weight <= bag.getCapacity()) && (cost >= bag.getMinimalCost());

            if (with || without) {
                configurationFounded = true;
            }

            return;
        }

        // with current item
        processRecursion(level + 1,
                         weight + currentItem.getWeight(),
                         cost + currentItem.getCost(),
                         costEstimate - currentItem.getCost());

        // without current item
        processRecursion(level + 1,
                         weight,
                         cost,
                         costEstimate - currentItem.getCost());
    }
};


#endif //INC_01_BAGSOLVER_HPP
