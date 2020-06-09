cmake_minimum_required(VERSION 2.8.12)
project(ex3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -ldl")
link_libraries(stdc++fs)

add_executable(ex3 common/AbstractAlgorithm.h common/AlgorithmRegistration.h common/WeightBalanceCalculator.cpp common/WeightBalanceCalculator.h simulator/main.cpp common/InputUtility.cpp common/InputUtility.h common/AlgorithmManager.cpp common/AlgorithmManager.h common/AlgorithmRegistration.cpp common/Ship.cpp common/Ship.h common/Port.cpp common/Port.h common/Container.cpp common/Container.h simulator/Simulation.cpp simulator/Simulation.h common/Instruction.cpp common/Instruction.h
        algorithm/SimpleAlgorithm.cpp algorithm/SimpleAlgorithm.h common/AlgorithmError.cpp common/AlgorithmError.h simulator/Error.cpp simulator/Error.h common/DistanceToDestinationComparator.cpp common/DistanceToDestinationComparator.h common/ISO_6346.cpp common/ISO_6346.h common/OutputUtility.h common/OutputUtility.cpp common/GeneralUtility.h common/GeneralUtility.cpp algorithm/GenericAlgorithm.h algorithm/GenericAlgorithm.cpp algorithm/RandomAlgorithm.h algorithm/RandomAlgorithm.cpp simulator/SimulationUtility.cpp simulator/SimulationUtility.h simulator/ThreadPoolExecutor.h simulator/PreProcessingTasksProducer.h simulator/PreProcessingTasksProducer.cpp simulator/SimulationTasksProducer.cpp simulator/SimulationTasksProducer.h simulator/TravelData.cpp simulator/TravelData.h)
TARGET_LINK_LIBRARIES(ex3 LINK_PUBLIC ${CMAKE_DL_LIBS})
