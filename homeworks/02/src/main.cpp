#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>

#include "solver/SolverFactory.hpp"
#include "solver/Solver.hpp"
#include "solver/BfSolver.hpp"
#include "solver/BnbSolver.hpp"
#include "BagSolver.hpp"
#include "SolverResult.hpp"

#define REPEAT_NUMBER 1

int main(int argc, char **argv) {
    if (argc <= 2) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    std::string methodArgument = argv[1];

    // For each file:
    for (int i = 2; i < argc; ++i) {
        double fileMaxTime = 0;
        std::vector<Solver> fileSolversList;
        std::string fileName = argv[i];

        std::cout << "file: " << fileName << std::endl;
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error: Couldn't open the input file." << std::endl;
            return 2;
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
            fileSolversList.push_back(SolverFactory::fromString(methodArgument, bag));
        }

        std::vector<SolverResult> measuredInstanceData;
        // For each instance (as _BagSolver):
        for (auto &solver : fileSolversList) {
            std::vector<unsigned long> measuredNodes;
            bool isSolvable = false;

            // TIMER START
            auto start = std::chrono::high_resolution_clock::now();
            for (int l = 0; l < REPEAT_NUMBER; l++) {
                solver.solveBag();
                isSolvable = solver.isConfigurationFounded();
                measuredNodes.push_back(solver.getVisitedNodes());
            }
            auto finish = std::chrono::high_resolution_clock::now();
            // TIMER END
            std::chrono::duration<double> elapsed = (finish - start) / REPEAT_NUMBER;

            // TODO:
            if (PRINTING) {
                std::cout << "Elapsed time: " << std::fixed << std::setprecision(12) << elapsed.count() << "s, "
                          << "nodes average: " << std::setprecision(2) << nodesAverage << " nodes, "
                          << "configuration exists: " << isSolvable
                          << std::endl;
            }

            if (fileMaxTime < elapsed.count()) {
                fileMaxTime = elapsed.count();
            }
            measuredInstanceData.emplace_back(elapsed.count(), fileMaxTime);
        }

        if (PRINTING) {
            std::cout << "FINAL RESULTS:" << std::endl;
        }

        // We have all the measured data for the file.
        // Now we have to compute it's average.

        unsigned totalItemsCount = measuredInstanceData.size();
        double totalTimeAverage = 0;
        double totalNodesAverage = 0;

        for (auto &k : measuredInstanceData) {
            totalTimeAverage += k.getTime();
            totalNodesAverage += k.getNodes();
        }

        totalTimeAverage /= totalItemsCount;
        totalNodesAverage /= totalItemsCount;

        file.close();
    }
    return 0;
}
