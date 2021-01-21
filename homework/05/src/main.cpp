#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "Loader.hpp"
#include "GaSolver.hpp"

#define INITIAL_POPULATION_COUNT 500
#define POPULATION_COUNT 200
#define MAX_GENERATIONS_COUNT 200
#define TOURNAMENT_SIZE 3
#define ELITISM 2
#define MUTATION_PROBABILITY 30 // percent
#define CROSSOVER_PROBABILITY 70 // percent

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    if (argc <= 2) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    Loader loader = Loader(argv[1], argv[2]);
    Formula formula = loader.loadFormula();

    GaSolver solver = GaSolver(formula,
                               INITIAL_POPULATION_COUNT,
                               POPULATION_COUNT,
                               MAX_GENERATIONS_COUNT,
                               TOURNAMENT_SIZE,
                               ELITISM,
                               MUTATION_PROBABILITY,
                               CROSSOVER_PROBABILITY);


    // TIMER START
    auto start = std::chrono::high_resolution_clock::now();
    Chromosome result = solver.solve();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = (finish - start);
    auto durationInMicro = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    // TIMER END
    std::cout << durationInMicro << std::endl;

//    result.toString();

    return 0;
}
