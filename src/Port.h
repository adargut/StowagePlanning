/**
    Port.h
    Purpose: representation of port object
*/
#ifndef EX1_PORT_H
#define EX1_PORT_H

#include <string>
#include <vector>
#include "Container.h"
#include "Utility.h"


class Port {
private:
    std::string code;
    Containers containers;
public:
    Port(const std::string& code, const Containers& _containers);
//    bool loadContainer(const Container& container); TODO is this needed?
//    Container unloadContainer(const Container& container);
};


#endif //EX1_PORT_H
