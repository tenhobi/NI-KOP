#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "Loader.hpp"
#include "GaSolver.hpp"
#include "SAT/Formula.hpp"

#define INITIAL_POPULATION_COUNT 500
#define POPULATION_COUNT 200
#define MAX_GENERATIONS_COUNT 500
#define TOURNAMENT_SIZE 10
#define ELITISM 1
#define MUTATION_PROBABILITY 40 // percent
#define CROSSOVER_PROBABILITY 80 // percent

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    if (argc <= 1) {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    Loader loader = Loader(argv[1]);
    Formula formula = loader.loadFormula();

    GaSolver solver = GaSolver(formula,
                               INITIAL_POPULATION_COUNT,
                               POPULATION_COUNT,
                               MAX_GENERATIONS_COUNT,
                               TOURNAMENT_SIZE,
                               ELITISM,
                               MUTATION_PROBABILITY,
                               CROSSOVER_PROBABILITY);
    Chromosome result = solver.solve();
    result.toString();
    std::cout << result.fitness << std::endl;

//    formula.toString();
    // uf20-01 6403
    // 1 2 3 4 -5
    // 6 7 8 9 10
    // 11 12 -13 14 -15
    // 16 17 18 19 20
//    std::vector<bool> vars = {
//            true, true, true, true, false,
//            true, true, true, true, true,
//            true, true, false, true, false,
//            true, true, true, true, true};
//    Chromosome chromosome;
//    chromosome = Chromosome(formula, vars);
//    chromosome.toString();
//    Chromosome b = chromosome.mutate();
//    b.toString();
//    std::cout << chromosome.calculateFitness() << std::endl;
//    std::cout << b.calculateFitness() << std::endl;
//    std::cout << chromosome.calculateFitness() << std::endl;


//
//    // TIMER START
//    auto start = std::chrono::high_resolution_clock::now();
//    Chromosome result = solver.solve();
//    auto finish = std::chrono::high_resolution_clock::now();
//    // TIMER END
//
//    std::chrono::duration<double> duration = (finish - start);
//    auto durationInMicro = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
//
//    // TODO: fetch reference result for id
//
//    // TODO: append to CSV argv[2]
//    // id, variables count, clauses count, time, result, reference result, ...?

    return 0;
}
