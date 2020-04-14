#include "Port.h"

Port::Port(std::string  _code, const ContainersVector& _containers) : code(std::move(_code)),
containers_to_load(_containers)
{
    for (auto& container : _containers) {
        PortContainers::value_type item(container->getId(), container);
        containers.insert(item);
    }
};

const Container* Port::unloadContainer(int container_id)
{
    if (containers.count(container_id) == 0) return nullptr;
    const Container* res = containers[container_id];
    containers.erase(container_id);
    return res;
}

bool Port::loadContainer(const Container* container) {
    if (containers.count(container->getId()) > 0) return false;
    PortContainers::value_type item(container->getId(), container);
    containers.insert(item);
    return true;
}

const ContainersVector& Port::getContainersToLoad() const {
    return containers_to_load;
}

const Port::PortContainers &Port::getContainers() const {
    return containers;
}

const std::string &Port::getCode() const {
    return code;
}
