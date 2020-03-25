#include "Container.h"

int Container::getWeight() const {
    return weight;
}

const std::string& Container::getPortCode() const {
    return port_code;
}

int Container::getId() const {
    return id;
}
