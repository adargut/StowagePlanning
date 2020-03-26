/**
    CargoShip.h
    Abstract cargo ship
*/
#ifndef EX1_CARGOSHIP_H
#define EX1_CARGOSHIP_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Floor.h"
#include "Port.h"
#include "Balancer.h"
#include "Container.h"
#include "Instruction.h"
#include "Utility.h"


class Ship {
private:
    int id;
    Floors empty_plan;
    Ports route;
    Balancer balancer; // TODO make concrete balancer
public:
    Ship (int _id, Floors& _plan, Ports& _route, Balancer& _balancer);
    int getId() const;
    const Floors& getEmptyPlan() const;
    bool loadContainer(int floor_idx, int row, int col, Container container_to_load);
    bool unloadContainer(int floor_idx, int row, int col);
    const Instructions& getInstructions(const Containers& containers_to_load);
};

class NaiveCargoShip : CargoShip {
private:
public:
};

#endif //EX1_CARGOSHIP_H
