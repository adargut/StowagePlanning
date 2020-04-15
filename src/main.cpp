#include <iostream>
#include <algorithm>
#include "Utility.h"
#include "Port.h"
#include "StowageAlgorithm.h"
#include "Simulation.h"
int main()
{
    Plan plan;
    Route route;
    Ports ports;
    if(!Utility::readShipPlan("Plan", plan)) std::cout << "TODO error\n";
    if(!Utility::readShipRoute("Route", route)) std::cout << "TODO error\n";
    if(!Utility::readPorts(route, ports)) std::cout << "TODO error\n";
    StowageAlgorithm* algorithm = new NaiveStowageAlgorithm();
    WeightBalanceCalculator* calculator = new NaiveWeightBalanceCalculator();
    Simulation simulation(ports, plan, route, calculator, algorithm, "travel_1");
    simulation.run_simulation();
    return 0;
}