//
// Created by osboxes on 5/14/20.
//

#include "Port.h"
#include "Container.h"

Port::Port(std::string code, const ContainersVector& containers) : m_code(std::move(code)),
           m_containersToLoad(containers)
{
    for (auto& container : containers)
    {
        m_containers[container->getId()] = container;
    }
}

std::shared_ptr<Container> Port::unloadContainer(const std::string& container_id)
{
    if (m_containers.count(container_id) == 0) return nullptr;
    auto res = m_containers[container_id];
    m_containers.erase(container_id);
    return res;
}

bool Port::loadContainer(std::shared_ptr<Container> container)
{
    //Trying to load a container already on the port
    if (m_containers.count(container->getId()) > 0) return false;
    m_containers[container->getId()] = container;
    return true;
}

const ContainersVector& Port::getContainersToLoad() const
{
    return m_containersToLoad;
}

const PortContainers &Port::getContainers() const
{
    return m_containers;
}

const std::string &Port::getCode() const
{
    return m_code;
}
