/**
    Simulation.h
    Perform simulation of the algorithm, assessing its correctness and efficiency
*/

#ifndef EX1_SIMULATION_H
#define EX1_SIMULATION_H

#include "Utility.h"
#include "StowageAlgorithm.h"

class Simulation {
private:
    Ship ship;
    Ports ports;
    StowageAlgorithm *algorithm;
    const std::string travel_name;
public:
    Simulation(Ports _ports, const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator,
               StowageAlgorithm *_algorithm, std::string _travel_name);

    void run_simulation();
};


#endif //EX1_SIMULATION_H
