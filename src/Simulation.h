/**
    Simulation.h
    Perform simulation of the algorithm, assessing its correctness and efficiency
*/

#ifndef EX1_SIMULATION_H
#define EX1_SIMULATION_H

#include "Utility.h"
#include "StowageAlgorithm.h"
#include <utility>
#include "AlgorithmError.h"

class Simulation {
private:
    Ship ship;
    StowageAlgorithm *algorithm;
    Ports ports;
    const std::string travel_name;
public:
    Simulation(Ports _ports, const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator,
               StowageAlgorithm *_algorithm, std::string _travel_name);
    /* Runs the algorithm given in the constructor and checks its validity and efficiency, results are shown in
     * simulation.results and errors in simulation.errors, individual port operations can be seen in their
     * corresponding files with their names */
    void runSimulation();
};

#endif //EX1_SIMULATION_H
