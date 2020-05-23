/**
    Container.h
    A container inside one of the ship's floors
*/

#ifndef EX1_CONTAINER_H
#define EX1_CONTAINER_H

#include <vector>
#include <string>
#include <utility>
#include "Utility.h"

class Container {
private:
    const int weight;
    const std::string port_code;
    const std::string id;
public:
    Container(int weight, std::string  portCode, std::string id);
    const std::string& getPortCode() const;
    int getWeight() const;
    const std::string& getId() const;
};

// Functor for hashing containers based on id
struct HashContainer {
    std::size_t operator()(const Container* _container) const {
        return std::hash<std::string>()(_container->getId());
    }
};

#endif //EX1_CONTAINER_H
