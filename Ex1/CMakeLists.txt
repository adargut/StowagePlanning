cmake_minimum_required(VERSION 2.8.12)
project(Ex1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

add_executable(Ex1 src/main.cpp src/Ship.cpp src/Ship.h src/Port.cpp src/Port.h src/Container.cpp src/Container.h src/WeightBalanceCalculator.cpp src/WeightBalanceCalculator.h src/Instruction.cpp src/Instruction.h src/Utility.cpp src/Utility.h src/StowageAlgorithm.cpp src/StowageAlgorithm.h src/Ship.cpp src/Ship.h src/Simulation.cpp src/Simulation.h src/AlgorithmError.cpp src/AlgorithmError.h src/Error.cpp src/Error.h)
