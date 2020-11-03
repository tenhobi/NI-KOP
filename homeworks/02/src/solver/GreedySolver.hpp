#ifndef INC_01_GREEDYSOLVER_HPP
#define INC_01_GREEDYSOLVER_HPP


#include <stack>
#include <utility>
#include <iostream>
#include <algorithm>
#include "Solver.hpp"


class GreedySolver : public Solver {
public:
    explicit GreedySolver(Bag &bag, bool isModification) : Solver(bag), isModification(isModification) {}

    void solve() override {
        solveGreedy();
    }

    void print() override {
        std::cout << bag.id << " " << bag.n << " " << resultCost;

        for (auto &&item : greedyDataFlag) {
            std::cout << " " << (item ? "1" : "0");
        }

        std::cout << std::endl;
    }

private:
    class GreedyData {
    public:
        int position;
        double ratio;

        GreedyData(int position, double ratio) :
                position(position),
                ratio(ratio) {}

        bool operator<(const GreedyData &other) const {
            return ratio < other.ratio;
        }
    };

    std::vector<bool> greedyDataFlag;
    unsigned long resultCost = 0;
    unsigned long resultWeight = 0;
    bool isModification;

    void solveGreedy() {
        // INITIALIZE

        std::vector<GreedyData> greedyData;
        greedyDataFlag = std::vector<bool>();

        for (unsigned long i = 0; i < bag.items.size(); ++i) {
            greedyData.emplace_back(i, (double) bag.items[i].getCost() / (double) bag.items[i].getWeight());
            greedyDataFlag.emplace_back(false);
        }

        std::sort(greedyData.begin(), greedyData.end());
        std::reverse(greedyData.begin(), greedyData.end());

        // COMPUTE

        unsigned long weight = 0;
        unsigned long cost = 0;

        for (auto &item : greedyData) {
            unsigned long itemCapacity = bag.items[item.position].getWeight();

            if (bag.capacity >= weight + itemCapacity) {
                weight += itemCapacity;
                cost += bag.items[item.position].getCost();
                greedyDataFlag[item.position] = true;
            }
        }

        resultCost = cost;
        resultWeight = weight;

        if (isModification) {
            bool someItemCanFitFlag = false;
            unsigned bestItemId = 0;
            unsigned bestCost = 0;
            unsigned bestWeight = 0;
            unsigned greedyCost = resultCost;

            for (unsigned long i = 0; i < bag.items.size(); ++i) {
                if (bag.items[i].getCost() > bestCost && bag.capacity >= bag.items[i].getWeight()) {
                    bestCost = bag.items[i].getCost();
                    bestItemId = i;
                    someItemCanFitFlag = true;
                }
            }

            if (greedyCost > bestCost || !someItemCanFitFlag) {
                // keep resultCost and resultWeight from standard greedy
            } else {
                // single item is better
                resultCost = bestCost;
                resultWeight = bestWeight;
                for (unsigned long i = 0; i < bag.items.size(); ++i) {
                    greedyDataFlag[i] = i == bestItemId;
                }
            }
        }
    }
};


#endif //INC_01_BFSOLVER_HPP
