//
// Created by osboxes on 5/14/20.
//

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
    PortContainers m_containers;
    ContainersVector m_containersToLoad;
public:
    Port(std::string code, const ContainersVector &containers);
    const std::string &getCode() const;
    const PortContainers &getContainers() const;
    const ContainersVector &getContainersToLoad() const;
    // TODO is this really weak ptr?
    std::shared_ptr<Container> unloadContainer(const std::string& container_id);
    bool loadContainer(Container* container);
};


#endif //EX2_PORT_H
