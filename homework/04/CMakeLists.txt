cmake_minimum_required(VERSION 3.10)
project(04)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -pedantic")

include_directories(src)
include_directories(src/solver)

add_executable(04
        src/main.cpp
        src/Item.hpp
        src/Bag.hpp
        src/solver/Solver.hpp)
