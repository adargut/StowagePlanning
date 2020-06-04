
#include "DistanceToDestinationComparator.h"

// Constructor
DistanceToDestinationComparator::DistanceToDestinationComparator(int currentPortIdx, const Route &route)
        : current_port_idx(currentPortIdx), route(route) {}

// Comparator
bool DistanceToDestinationComparator::operator()(std::shared_ptr<Container> c1, std::shared_ptr<Container> c2)
{
    return distanceToDestination(c1) < distanceToDestination(c2);
}

// Compute distance container has until destination
int DistanceToDestinationComparator::distanceToDestination(std::shared_ptr<Container> container)
{
    // Invalid containers should be placed last in the sort order
    if (!ISO_6346::isValidId(container->getId())) return INT_MAX;
    if (container->getWeight() == BAD_WEIGHT) return INT_MAX;

    for (int i = current_port_idx + 1; i < int(route.size()); i++)
    {
        if (route[i] == (container->getPortCode())) return (i - current_port_idx);
    }
    return INT_MAX; // Infinite
}