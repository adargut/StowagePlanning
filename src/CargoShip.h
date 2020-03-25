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

class Ship {
    typedef typename std::vector <Floor> Floors;
    typedef typename std::vector <Container> Containers; // TODO maybe use dict instead of vector?
    typedef typename std::vector <std::string> Ports;
    typedef typename std::vector <Instruction> Instructions;
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

#endif //EX1_CARGOSHIP_H
