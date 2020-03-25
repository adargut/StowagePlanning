cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ex1 main.cpp CargoShip.cpp CargoShip.h Floor.cpp Floor.h Port.cpp Port.h Crane.cpp Crane.h Container.cpp Container.h Balancer.cpp Balancer.h Instruction.cpp Instruction.h NaiveCargoShip.cpp NaiveCargoShip.h Utility.cpp Utility.h StowageAlgorithm.cpp StowageAlgorithm.h)