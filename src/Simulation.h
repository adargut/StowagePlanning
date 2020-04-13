//
// Created by Nir on 13/04/2020.
//

#ifndef EX1_SIMULATION_H
#define EX1_SIMULATION_H

#include "Utility.h"
#include "StowageAlgorithm.h"
class Simulation {
private:
    Ship ship;
    Ports ports;
    StowageAlgorithm* algorithm;
    Simulation(const Ports& _ports, const Plan& _plan, const Route& _route,
            WeightBalanceCalculator* _calculator, StowageAlgorithm* _algorithm);
    bool run_simulation();
};


#endif //EX1_SIMULATION_H
