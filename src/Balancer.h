/**
    Balancer.h
    Weight balancer that checks the balance an instruction set
*/
#ifndef EX1_BALANCER_H
#define EX1_BALANCER_H
#define BALANCED -1

#include <vector>
#include "Instruction.h"
#include "Utility.h"

class Balancer {
protected:
    const Plan& ship_plan;
public:
    Balancer(const Plan& ship_plan);
    virtual int checkBalance(const Instructions& instructions, const std::vector<int>& weights) = 0;
};

class NaiveBalancer: public Balancer {
public:
    NaiveBalancer(const Plan &ship_plan);
    int checkBalance(const Instructions &instructions, const std::vector<int> &weights) override;
};

#endif //EX1_BALANCER_H
