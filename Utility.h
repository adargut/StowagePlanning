//
// Created by Adar on 26/03/2020.
//

#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <vector>
#include "Instruction.h"
#include "Port.h"
#include "CargoShip.h"
#include "StowageAlgorithm.h"

typedef typename std::vector <Instruction> Instructions;
typedef typename std::vector <std::string> Ports;

bool performInstructions(Ship& ship, Port& port, Instructions& instructions);
void runSimulation(Ship& ship, Ports ports, StowageAlgorithm algorithm);

#endif //EX1_UTILITY_H
