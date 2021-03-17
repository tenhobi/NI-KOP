cmake_minimum_required(VERSION 3.10)
project(05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -pedantic")

include_directories(src)
include_directories(src/solver)

add_executable(05
        src/main.cpp
        src/Chromosome.hpp
        src/GaSolver.hpp
        src/SAT/Clause.hpp src/SAT/Formula.hpp
        src/Loader.hpp)
