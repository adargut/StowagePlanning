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
#include "Balancer.h"
#include "Container.h"
#include "Instruction.h"
#include "Utility.h"

class Ship {
private:
    const int id;
    const Route route;
    const Balancer* balancer; // TODO make concrete balancer
    Plan plan;
    ContainerMap containers;
    int current_port_idx;
public:
    Ship (int _id, const Plan& _plan, const Route& _route, Balancer* _balancer);
    const Plan& getPlan() const;
    int getId() const;
    bool loadContainer(int floor_idx, int row, int col, Container container_to_load);
    bool unloadContainer(int floor_idx, int row, int col);
};

#endif //EX1_SHIP_H
