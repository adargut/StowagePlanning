/**
    Container.h
    A container inside one of the ship's floors
*/
#ifndef EX1_CONTAINER_H
#define EX1_CONTAINER_H

#include <vector>
#include <string>
#include "Utility.h"


class Container {
private:
    const int weight;
    const std::string port_code;
    const int id;
public:
    Container(int _weight, const std::string& _port_code, int _id);
    int getWeight() const;
    const std::string& getPortCode() const;
    int getId() const;
};


#endif //EX1_CONTAINER_H
