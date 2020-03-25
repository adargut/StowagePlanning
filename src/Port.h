#ifndef EX1_PORT_H
#define EX1_PORT_H

#include <string>
#include <vector>
#include "Container.h"

class Port {
    typedef typename std::vector <Container> Containers; // TODO maybe use dict instead of vector?
private:
    std::string code;
    Containers containers;
public:
    Port(const std::string& code, const Containers& _containers);
//    bool loadContainer(const Container& container); TODO is this needed?
//    Container unloadContainer(const Container& container);
};


#endif //EX1_PORT_H
