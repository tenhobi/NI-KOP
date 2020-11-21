#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

#include "solver/SolverFactory.hpp"

#define REPEAT_NUMBER 1

int main(int argc, char **argv) {
    if (argc <= 2) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    std::string methodArgument = argv[1];

    // For each file:
    for (int i = 2; i < argc; ++i) {
        double totalTimeMax = 0;
        std::vector<Solver *> fileSolversList;
        std::string fileName = argv[i];

        std::cout << "file: " << fileName << std::endl;
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error: Couldn't open the input file." << std::endl;
            return 2;
        }

        // Init each instance:
        while (true) {
            int id, n, bagCapacity;
            file >> id;

            if (file.eof()) {
                break;
            }

            file >> n >> bagCapacity;

            // <weight, cost>
            std::vector<Item> bagItems;

            // For each item:
            for (int j = 0; j < n; ++j) {
                unsigned long weight, cost;

                file >> weight >> cost;
                bagItems.emplace_back(weight, cost);
            }

            Bag bag = Bag(id, n, bagItems, bagCapacity);
            fileSolversList.push_back(SolverFactory::fromString(methodArgument, bag));
        }

        std::vector<double> instancesTimes;
        // For each instance:
        for (auto &solver : fileSolversList) {
            std::vector<unsigned long> measuredNodes;

            // TIMER START
            auto start = std::chrono::high_resolution_clock::now();
            for (int l = 0; l < REPEAT_NUMBER; l++) {
                solver->solve();
            }
            auto finish = std::chrono::high_resolution_clock::now();
            // TIMER END
            std::chrono::duration<double> duration = (finish - start) / REPEAT_NUMBER;
            auto durationInMicro = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

            solver->print();

            if (totalTimeMax < durationInMicro) {
                totalTimeMax = durationInMicro;
            }
            instancesTimes.emplace_back(durationInMicro);
        }

        // We have all the measured data for the file.
        // Now we have to compute it's average.
        unsigned totalItemsCount = instancesTimes.size();
        double totalTimeAverage = 0;
        for (auto &k : instancesTimes) {
            totalTimeAverage += k;
        }
        totalTimeAverage /= totalItemsCount;

        std::cout << "FOR FILE:" << std::endl
                  << "Average time: " << std::fixed << std::setprecision(6) << totalTimeAverage << "s, "
                  << "Max time: " << std::fixed << std::setprecision(6) << totalTimeMax << "s, "
                  << std::endl;

        file.close();
    }
    return 0;
}
