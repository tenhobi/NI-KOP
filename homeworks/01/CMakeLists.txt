cmake_minimum_required(VERSION 3.10)
project(01)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/strategy)

add_executable(01
        src/strategy/BnbStrategy.hpp
        src/strategy/BruteForceStrategy.hpp
        src/strategy/Strategy.hpp
        src/BagSolver.hpp
        src/BagSolverMethod.hpp
        src/DecisionResult.hpp
        src/main.cpp)
