cmake_minimum_required(VERSION 2.8.12)
project(Ex2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -ldl")
link_libraries(stdc++fs)

add_executable(Ex2 Common/AbstractAlgorithm.h Common/AlgorithmRegistration.h Common/WeightBalanceCalculator.cpp Common/WeightBalanceCalculator.h Simulator/main.cpp Common/InputUtility.cpp Common/InputUtility.h Common/AlgorithmManager.cpp Common/AlgorithmManager.h Common/AlgorithmRegistration.cpp Common/Ship.cpp Common/Ship.h Common/Port.cpp Common/Port.h Common/Container.cpp Common/Container.h Simulator/Simulation.cpp Simulator/Simulation.h Common/Instruction.cpp Common/Instruction.h
        Algorithm/SimpleAlgorithm.cpp Algorithm/SimpleAlgorithm.h Common/AlgorithmError.cpp Common/AlgorithmError.h Simulator/Error.cpp Simulator/Error.h Common/DistanceToDestinationComparator.cpp Common/DistanceToDestinationComparator.h Common/ISO_6346.cpp Common/ISO_6346.h Common/OutputUtility.h Common/OutputUtility.cpp Common/GeneralUtility.h Common/GeneralUtility.cpp Algorithm/GenericAlgorithm.h Algorithm/GenericAlgorithm.cpp Algorithm/RandomAlgorithm.h Algorithm/RandomAlgorithm.cpp)
TARGET_LINK_LIBRARIES(Ex2 LINK_PUBLIC ${CMAKE_DL_LIBS})
