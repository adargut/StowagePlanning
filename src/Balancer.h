/**
    Balancer.h
    Weight balancer that checks the balance an instruction set
*/
#ifndef EX1_BALANCER_H
#define EX1_BALANCER_H

#include <vector>
#include "Floor.h"
#include "Instruction.h"
#include "Utility.h"


class Balancer {
public:
    virtual int checkBalance(const Instructions& instructions) = 0;
private:
    Floors& ship_plan;
};

class NaiveBalancer:Balancer {
public:
    NaiveBalancer(Floors& _ship_plan);
};


#endif //EX1_BALANCER_H
