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
    const std::string port_code;
    const int weight;
    const int id;
public:
    Container(int _weight, const std::string& _port_code, int _id);
    const std::string& getPortCode() const;
    int getWeight() const;
    int getId() const;
};


#endif //EX1_CONTAINER_H
