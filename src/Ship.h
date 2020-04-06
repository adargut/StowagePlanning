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

class Ship {
private:
    const int id;
    Route route;
    Plan plan;
    ContainerMap containers;
    WeightBalanceCalculator* calculator; // TODO make concrete balancer
    int current_port_idx;
    void updatePlan(int floor, int row, int col, int id);
    void updateContainerMap(int floor, int row, int col, int id,  const Container *const container);
    void updateContainerMap(int floor, int row, int col);
public:
    explicit Ship (int _id);
    bool readShipPlan(const std::string& path);
    bool readShipRoute(const std::string& path);
    void setWeightBalanceCalculator(WeightBalanceCalculator* _calculator);
    const Plan& getPlan() const;
    const Route& getRoute() const;
    //int getId() const;
    bool loadContainer(int floor, int row, int col, const Container * const container_to_load);
    const Container* const unloadContainer(int floor, int row, int col);
    ~Ship(); // TODO: free calculator
};

#endif //EX1_SHIP_H
