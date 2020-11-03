#ifndef INC_01_FPTASSOLVER_HPP
#define INC_01_FPTASSOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include <iostream>
#include <cmath>
#include "DynSolver.hpp"


class FptasSolver : public DynSolver {
public:
    explicit FptasSolver(Bag &bag) : DynSolver(bag) {}

    void solve() override {
        solveFptas();
    }

    void print() override {
        std::cout << bag.id << " " << bag.n << " " << resultCost;

        for (auto &&item : itemsFlag) {
            std::cout << " " << (item ? "1" : "0");
        }

        std::cout << std::endl;
    }

private:
    double error = 1.0;

    void solveFptas() {
        // INITIALIZATION
        unsigned long maxCost = 0;
        unsigned long numberOfItems = bag.n;

        for (auto &item : bag.items) {
            if (item.getCost() > maxCost) {
                maxCost = item.getCost();
            }
        }

        // FPTAS vars

        double k = (error * (double) maxCost) / (double) numberOfItems;
        //double b = std::floor(std::log2(k)); // bits
        //double reduction = std::pow(2, b);

        Bag bagForDynamic = Bag(bag.id, bag.n, std::vector<Item>(), bag.capacity);
        auto oldBag = bag;
        bag = bagForDynamic;
        solveDyn();

        // COMPUTE

        for (unsigned long i = 0; i < numberOfItems; i++) {
            unsigned long tmpCost = std::floor((double) oldBag.items[i].getCost() / k);
            bagForDynamic.items.emplace_back(oldBag.items[i].getWeight(), tmpCost);
        }

        unsigned long tmpResultCost = 0;
        unsigned long tmpResultWeight = 0;

        for (unsigned long i = 0; i < itemsFlag.size(); ++i) {
            if (itemsFlag[i]) {
                tmpResultCost += oldBag.items[i].getCost();
                tmpResultWeight += oldBag.items[i].getWeight();
            }
        }

        resultCost = tmpResultCost;
        resultWeight = tmpResultWeight;
    }
};


#endif //INC_01_FPTASSOLVER_HPP
