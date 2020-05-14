//
// Created by osboxes on 5/14/20.
//

#include "Container.h"


Container::Container(int weight, std::string portCode, std::string id) :
        m_weight(weight), m_portCode(std::move(portCode)), m_id(id) {}

const std::string &Container::getPortCode() const
{
    return m_portCode;
}

int Container::getWeight() const
{
    return m_weight;
}

const std::string& Container::getId() const
{
    return m_id;
}

