#ifndef EX2_DISTANCETODESTINATIONCOMPARATOR_H
#define EX2_DISTANCETODESTINATIONCOMPARATOR_H

#include <climits>
#include "GeneralUtility.h"
#include "Container.h"
#include "ISO_6346.h"

/**
 * @brief DistanceToDestination.h compares the distance of different containers to their destination
 * 
 */
class DistanceToDestinationComparator 
{
private:
    int current_port_idx;
    const Route &route;
public:
    DistanceToDestinationComparator(int currentPortIdx, const Route &route);
    int distanceToDestination(std::shared_ptr<Container> container);
    bool operator()(std::shared_ptr<Container> c1, std::shared_ptr<Container> c2);
};


#endif //EX2_DISTANCETODESTINATIONCOMPARATOR_H
