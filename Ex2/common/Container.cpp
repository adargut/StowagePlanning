#include "Container.h"

// Constructor
Container::Container(int weight, std::string portCode, std::string id) :
        m_weight(weight), m_portCode(std::move(portCode)), m_id(id) {}

// Port code geter
const std::string &Container::getPortCode() const
{
    return m_portCode;
}

// Weight getter
int Container::getWeight() const
{
    return m_weight;
}

// ID getter
const std::string& Container::getId() const
{
    return m_id;
}

// Weight setter
void Container::setWeight(int mWeight) 
{
    m_weight = mWeight;
}

// Port code setter
void Container::setPortCode(const std::string &mPortCode) 
{
    m_portCode = mPortCode;
}

// ID setter
void Container::setId(const std::string &mId) 
{
    m_id = mId;
}
