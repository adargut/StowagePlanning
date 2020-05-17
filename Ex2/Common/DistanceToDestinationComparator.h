//
// Created by nir on 16/05/2020.
//

#ifndef EX2_DISTANCETODESTINATIONCOMPARATOR_H
#define EX2_DISTANCETODESTINATIONCOMPARATOR_H

#include <climits>
#include "GeneralUtility.h"
#include "Container.h"

class DistanceToDestinationComparator {
private:
    int current_port_idx;
    const Route &route;
public:
    DistanceToDestinationComparator(int currentPortIdx, const Route &route);
    // Returns distance from container to destination based on current port index
    int distanceToDestination(std::shared_ptr<Container> container);
    bool operator()(std::shared_ptr<Container> c1, std::shared_ptr<Container> c2);
};


#endif //EX2_DISTANCETODESTINATIONCOMPARATOR_H
