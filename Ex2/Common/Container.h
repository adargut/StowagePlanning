//
// Created by osboxes on 5/14/20.
//

#ifndef EX2_CONTAINER_H
#define EX2_CONTAINER_H

#include <vector>
#include <string>
#include "GeneralUtility.h"


class Container
{
private:
    int m_weight = BAD_WEIGHT;
    std::string m_portCode = BAD_DESTINATION;
    std::string m_id;
public:
    Container() = default;
    Container(int weight, std::string portCode, std::string id);
    const std::string& getPortCode() const;
    int getWeight() const;
    const std::string& getId() const;
    void setWeight(int mWeight);
    void setPortCode(const string &mPortCode);
    void setId(const string &mId);
};

// Functor for hashing containers based on id
struct HashContainer
{
    // TODO this needs to be shared_ptr?
    std::size_t operator()(const Container* _container) const {
        return std::hash<std::string>()(_container->getId());
    }
};


#endif //EX2_CONTAINER_H
