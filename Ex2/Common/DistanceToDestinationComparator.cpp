//
// Created by nir on 16/05/2020.
//

#include "DistanceToDestinationComparator.h"
DistanceToDestinationComparator::DistanceToDestinationComparator(const int &currentPortIdx, const Route &route)
        : current_port_idx(currentPortIdx), route(route) {}

bool DistanceToDestinationComparator::operator()(std::shared_ptr<Container> c1, std::shared_ptr<Container> c2)
{
    return distanceToDestination(c1) < distanceToDestination(c2);
}

int DistanceToDestinationComparator::distanceToDestination(std::shared_ptr<Container> container)
{
    for (int i = current_port_idx + 1; i < int(route.size()); i++)
    {
        if (route[i] == (container->getPortCode())) return (i - current_port_idx);
    }
    return INT_MAX; // Infinite
}