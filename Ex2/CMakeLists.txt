cmake_minimum_required(VERSION 2.8.12)
project(Ex2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

add_executable(Ex2 main.cpp Common/AbstractAlgorithm.h Common/AlgorithmRegistration.h Simulator/AlgorithmRegistration.cpp Common/WeightBalanceCalculator.cpp Common/WeightBalanceCalculator.h Simulator/main.cpp Common/InputUtility.cpp Common/InputUtility.h)