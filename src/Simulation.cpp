//
// Created by Nir on 13/04/2020.
//

#include "Simulation.h"

Simulation::Simulation(const Ports& _ports, const Plan& _plan, const Route& _route,
                       WeightBalanceCalculator* _calculator, StowageAlgorithm* _algorithm)
                       : ship(_plan, _route, _calculator), algorithm(_algorithm)
{
    //ports = _ports;
}

bool Simulation::run_simulation() {
    //TODO reset algorithm
    int number_of_operations = 0;
    for (auto& port : ports)
    {
        Instructions instructions = algorithm->getInstructionsForCargo(port.getContainersToLoad());
        number_of_operations+=instructions.size();
        for (auto& instruction : instructions)
        {
            if(instruction.getOp() == Instruction::Unload)
            {

            }
            if(instruction.getOp() == Instruction::Load)
            {

            }
            if(instruction.getOp() == Instruction::Reject)
            {

            }
            //TODO Check that we rejected the containers with the latest destinations
        }
    }
    return false;
}
