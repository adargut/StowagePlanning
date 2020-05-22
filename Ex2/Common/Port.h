//
// Created by osboxes on 5/14/20.
//
/* Class to represent a port's state */
#ifndef EX2_PORT_H
#define EX2_PORT_H

#include <string>
#include <vector>
#include <memory>
#include "GeneralUtility.h"


class Port
{
private:
    const std::string m_code;
    PortContainers m_containers; // Containers currently on the port (map of id->container)
    ContainersVector m_containersToLoad; // Containers originally meant to be loaded from that port
public:
    Port(std::string code, const ContainersVector& containers);
    const std::string &getCode() const;
    const PortContainers &getContainers() const;
    const ContainersVector &getContainersToLoad() const;
    std::shared_ptr<Container> unloadContainer(const std::string& container_id);
    bool loadContainer(std::shared_ptr<Container> container);
};


#endif //EX2_PORT_H
