#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>

#include "strategy/Strategy.hpp"
#include "strategy/BruteForceStrategy.hpp"
#include "strategy/BnbStrategy.hpp"
#include "BagSolver.hpp"

#define REPEAT_NUMBER 1
#define PRINTING 0
#define HISTOGRAM 0

int main(int argc, char **argv) {
    if (argc <= 2) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    std::string methodArgument = argv[1];
    Strategy *method;
    if (methodArgument == "bf") {
        method = new BruteForceStrategy();
    } else if (methodArgument == "bnb") {
        method = new BnbStrategy();
    } else {
        std::cout << "Error: Invalid method argument." << std::endl;
        return 2;
    }

    // For each file:
    for (int i = 2; i < argc; ++i) {
        double totalTimeMax = 0;
        std::vector<BagSolver> bagSolverList;

        std::string fileName = argv[i];

        std::cout << "file: " << fileName << std::endl;
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error: Couldn't open the input file." << std::endl;
            return 4;
        }

        // Each instance:
        while (true) {
            int id, n, bagCapacity, minimalCost;
            file >> id;

            if (file.eof()) {
                break;
            }

            file >> n >> bagCapacity >> minimalCost;
            id = -id;

            // <weight, cost>
            std::vector<Item> bagItems;

            // For each item:
            for (int j = 0; j < n; ++j) {
                unsigned long weight, cost;

                file >> weight >> cost;
                bagItems.emplace_back(weight, cost);
            }

            Bag bag = Bag(bagItems, bagCapacity, minimalCost);
            bagSolverList.emplace_back(method, bag);
        }



        std::vector<std::pair<double, double>> measuredData;
        // For each instance (as _BagSolver):
        for (auto &k : bagSolverList) {
            std::vector<unsigned long> measuredNodes;
            bool isSolvable = false;

            // TIMER START
            auto start = std::chrono::high_resolution_clock::now();
            for (int l = 0; l < REPEAT_NUMBER; l++) {
                k.solveBag();
                isSolvable = k.isConfigurationFounded();
                measuredNodes.push_back(k.getVisitedNodes());
            }
            auto finish = std::chrono::high_resolution_clock::now();
            // TIMER END
            std::chrono::duration<double> elapsed = (finish - start) / REPEAT_NUMBER;

            double nodesAverage =
                    std::accumulate(measuredNodes.begin(), measuredNodes.end(), 0.0) / (REPEAT_NUMBER * 1.0);

            if (PRINTING) {
                std::cout << "Elapsed time: " << std::fixed << std::setprecision(12) << elapsed.count() << "s, "
                          << "nodes average: " << std::setprecision(2) << nodesAverage << " nodes, "
                          << "configuration exists: " << isSolvable
                          << std::endl;
            }

            if (HISTOGRAM) {
                std::cout << nodesAverage << std::endl;
            }

            if (totalTimeMax < elapsed.count()) {
                totalTimeMax = elapsed.count();
            }
            measuredData.emplace_back(elapsed.count(), nodesAverage);
        }

        if (PRINTING) {
            std::cout << "FINAL RESULTS:" << std::endl;
        }

        // We have all the measured data for the file.
        // Now we have to compute it's average.

        unsigned totalItemsCount = measuredData.size();
        double totalTimeAverage = 0;
        double totalNodesAverage = 0;

        for (auto &k : measuredData) {
            totalTimeAverage += k.first;
            totalNodesAverage += k.second;
        }

        totalTimeAverage /= totalItemsCount;
        totalNodesAverage /= totalItemsCount;

        if (!HISTOGRAM) {
            std::cout
                    << std::fixed << std::setprecision(12) << totalTimeAverage << " s, "
                    << std::setprecision(2) << totalNodesAverage << " nodes"
                    << std::endl;

            std::cout << "max time: " << std::fixed << std::setprecision(12) << totalTimeMax << " s, " << std::endl;
        }

        file.close();
    }
    return 0;
}
