/**
    Port.h
    Purpose: representation of port object
*/

#ifndef EX1_PORT_H
#define EX1_PORT_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "Utility.h"
#include "Container.h"

class Port {
public:
    // TODO move me to utility
    // TODO change to unordered map, with key = id
    typedef typename std::unordered_map<int, const Container*> PortContainers;
private:
    const std::string code;
    PortContainers containers;
    ContainersVector containers_to_load;
public:
    Port(std::string  _code, const ContainersVector& _containers);
    const std::string &getCode() const;
    const PortContainers &getContainers() const;
    const ContainersVector &getContainersToLoad() const;
    // TODO change to work with keys (id)
    const Container* unloadContainer(int container_id);
    bool loadContainer(const Container* container);
};

#endif //EX1_PORT_H
