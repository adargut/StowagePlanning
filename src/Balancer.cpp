#include "Balancer.h"

Balancer::Balancer(const Plan& ship_plan) : ship_plan(ship_plan) {};

NaiveBalancer::NaiveBalancer(const Plan& ship_plan) : Balancer(ship_plan) {};

int NaiveBalancer::checkBalance(const Instructions &instructions, const std::vector<int> &weights) {
    return BALANCED; // for now, balancer always returns balanced
}