#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>

#include "BagSolver.hpp"

#define REPEAT_NUMBER 1

int main(int argc, char **argv) {
    if (argc <= 3) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    std::string methodArgument = argv[1];
    if (methodArgument != "bf" && methodArgument != "bnb") {
        std::cout << "Error: Invalid method argument." << std::endl;
        return 2;
    }
    BagSolverMethod method = methodArgument == "bf" ? BagSolverMethod::BrutalForce : BagSolverMethod::BnB;

    std::string printArgument = argv[2];
    if (printArgument != "true" && printArgument != "false") {
        std::cout << "Error: Invalid printing argument." << std::endl;
        return 3;
    }
    bool printing = printArgument == "true";

    // For each file:
    for (int i = 3; i < argc; ++i) {
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
            std::vector<std::pair<unsigned long, unsigned long>> bag;

            // For each item:
            for (int j = 0; j < n; ++j) {
                unsigned long weight, cost;

                file >> weight >> cost;
                bag.emplace_back(weight, cost);
            }

            bagSolverList.emplace_back(id, bag, bagCapacity, minimalCost, method);
        }

        std::vector<std::pair<double, double>> measuredData;
        // For each instance (as BagSolver):
        for (auto &k : bagSolverList) {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<unsigned long> measuredNodes;

            for (int l = 0; l < REPEAT_NUMBER; l++) {
                DecisionResult result = k.isSolvable(printing && (l == 0));
                measuredNodes.push_back(result.nodesVisited);
            }
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = (finish - start) / REPEAT_NUMBER;

            if (printing) {
                std::cout << "Elapsed time: " << std::fixed << std::setprecision(12) << elapsed.count() << "s"
                          << std::endl;
            }

            double nodesAverage =
                    std::accumulate(measuredNodes.begin(), measuredNodes.end(), 0.0) / (REPEAT_NUMBER * 1.0);

            measuredData.emplace_back(elapsed.count(), nodesAverage);
        }

        if (printing) {
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

        std::cout
                << std::fixed << std::setprecision(12) << totalTimeAverage << " s, "
                << std::setprecision(2) << totalNodesAverage << " nodes"
                << std::endl;

        file.close();
    }
    return 0;
}
