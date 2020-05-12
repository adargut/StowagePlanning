/**
    Ship.h
    A class for a ship carrying containers from ports to their destinations
*/

#ifndef EX1_SHIP_H
#define EX1_SHIP_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Port.h"
#include "WeightBalanceCalculator.h"
#include "Container.h"
#include "Instruction.h"
#include "Utility.h"

// TODO rework this class from Ex1

class Ship {
private:
    Route route;
    Plan plan;
    ContainerMap containers;
    // TODO make concrete balancer
    WeightBalanceCalculator* calculator;
    int current_port_idx = 0;
public:
    explicit Ship (const Plan& _plan, const Route& _route, WeightBalanceCalculator* _calculator);
    const Plan& getPlan() const;
    const Route& getRoute() const;
    const int& getPortIndex() const;
    const ContainerMap& getContainerMap() const;
    WeightBalanceCalculator *getCalculator() const;
    /* Load the container to the lowest available floor where this position is unoccupied,
     * return false if no position is available, and true otherwise */
    bool loadContainer(int floor, int row, int col, Container * container_to_load);
    // Unload the top container in this position, returns nullptr if none exists
    Container * unloadContainer(int floor, int row, int col);
    void advanceCurrentPortIdx();
    bool isShipFull();
private:
    void updatePlan(int floor, int row, int col, const std::string& val);
    void insertContainerMap(int floor, int row, int col, const std::string& id, Container * container);
    void eraseContainerMap(int floor, int row, int col);
};

#endif //EX1_SHIP_H
