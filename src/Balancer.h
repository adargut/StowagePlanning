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
    virtual int checkBalance(const Instructions& instructions, const std::vector<int>& weights) = 0;
private:
    const Plan& ship_plan;
};

class NaiveBalancer: public Balancer {
public:
    NaiveBalancer(const Plan& _ship_plan);
};


#endif //EX1_BALANCER_H
