#include "Port.h"

Port::Port(std::string  _code, const ContainersVector& _containers) : code(std::move(_code)) {
    for (auto container : _containers) {
        containers.insert(container);
    }
};

bool Port::unloadContainer(const Container* container) {
    if (containers.count(container) == 0) return false; // TODO return error
    containers.erase(container);
    return true;
}

bool Port::loadContainer(const Container* container) {
    if (containers.count(container) > 0) return false; // TODO return real error
    containers.insert(container);
    return true;
}
