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
    typedef typename std::unordered_set<const Container*, HashContainer> PortContainers;
private:
    const std::string code;
    PortContainers containers;
public:
    Port(std::string  _code, const ContainersVector& _containers);
    bool unloadContainer(const Container* container);
    bool loadContainer(const Container* container);
};

#endif //EX1_PORT_H
