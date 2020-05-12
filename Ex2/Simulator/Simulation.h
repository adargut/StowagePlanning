//
// Created by nir on 12/05/2020.
//

#ifndef EX2_SIMULATION_H
#define EX2_SIMULATION_H
#include "../Common/AbstractAlgorithm.h"
#include <memory>
#include "../Common/Ship.h"
class Simulation {
     std::unique_ptr<AbstractAlgorithm> algorithm;
     Ship ship;
};


#endif //EX2_SIMULATION_H
