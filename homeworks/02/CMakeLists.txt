cmake_minimum_required(VERSION 3.10)
project(01)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/solver)

add_executable(02
        src/solver/BnbSolver.hpp
        src/solver/BfSolver.hpp
        src/solver/Solver.hpp
        src/BagSolver.hpp
        src/Item.hpp
        src/Bag.hpp
        src/main.cpp src/solver/SolverFactory.hpp)
