#include "Container.h"

Container::Container(int _weight, std::string portCode, std::string _id) :
        weight(_weight), port_code(std::move(portCode)), id(_id) {}

const std::string &Container::getPortCode() const {
    return port_code;
}

int Container::getWeight() const {
    return weight;
}

const std::string& Container::getId() const {
    return id;
}
