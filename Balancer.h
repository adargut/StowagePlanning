#ifndef EX1_BALANCER_H
#define EX1_BALANCER_H

#include <vector>
#include "Floor.h"
#include "Instruction.h"


class Balancer {
    typedef typename std::vector <Floor> Floors;
    typedef typename std::vector <Instruction> Instructions;
public:
    Balancer(Floors& _ship_plan);
    virtual int checkBalance(const Instructions& instructions) = 0;
private:
    Floors& ship_plan;
};


#endif //EX1_BALANCER_H
