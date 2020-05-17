cmake_minimum_required(VERSION 2.8.12)
project(Ex2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -ldl")
link_libraries(stdc++fs)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

add_executable(Ex2 Common/AbstractAlgorithm.h Common/AlgorithmRegistration.h Common/WeightBalanceCalculator.cpp Common/WeightBalanceCalculator.h Simulator/main.cpp Common/InputUtility.cpp Common/InputUtility.h Common/AlgorithmManager.cpp Common/AlgorithmManager.h Common/AlgorithmRegistration.cpp Common/Ship.cpp Common/Ship.h Common/Port.cpp Common/Port.h Common/Container.cpp Common/Container.h Simulator/Simulation.cpp Simulator/Simulation.h Common/Instruction.cpp Common/Instruction.h
        Algorithm/SimpleAlgorithm.cpp Algorithm/SimpleAlgorithm.h Common/AlgorithmError.cpp Common/AlgorithmError.h Common/OutputUtility.h Common/OutputUtility.cpp)
TARGET_LINK_LIBRARIES(Ex2 LINK_PUBLIC ${Boost_LIBRARIES} ${CMAKE_DL_LIBS})
