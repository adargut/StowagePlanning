cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ex1 src/main.cpp src/Ship.cpp src/Ship.h src/Port.cpp src/Port.h src/Container.cpp src/Container.h src/WeightBalanceCalculator.cpp src/WeightBalanceCalculator.h src/Instruction.cpp src/Instruction.h src/Utility.cpp src/Utility.h src/StowageAlgorithm.cpp src/StowageAlgorithm.h src/Ship.cpp src/Ship.h)