/**
    StowageAlgorithm.h
    Algorithmic logic of stowage
*/
#ifndef EX1_STOWAGEALGORITHM_H
#define EX1_STOWAGEALGORITHM_H


class StowageAlgorithm { // TODO implement me
    const Plan& plan;
    const Route& route;
    const Balancer& balancer;
    Plan empty_plan;
    int current_port_idx;
public:
    StowageAlgorithm(const Plan& _plan, const Route& _route, const Balancer& _balancer);
    const Plan& getShipPlan() const;
    const Instructions& getInstructionsForCargo(const Containers& containers_to_load) const;
};


#endif //EX1_STOWAGEALGORITHM_H
