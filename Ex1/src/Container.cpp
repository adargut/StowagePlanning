#include "Container.h"

Container::Container(int _weight, std::string _port_code, std::string _id) :
weight(_weight), port_code(std::move(_port_code)), id(_id) {}

const std::string &Container::getPortCode() const {
    return port_code;
}

int Container::getWeight() const {
    return weight;
}

const std::string& Container::getId() const {
    return id;
}
