//
// Created by osboxes on 5/14/20.
//

#ifndef EX2_CONTAINER_H
#define EX2_CONTAINER_H

#include <vector>
#include <string>


class Container
{
private:
    const int m_weight;
    const std::string m_portCode;
    const std::string m_id;
public:
    Container(int weight, std::string portCode, std::string id);
    const std::string& getPortCode() const;
    int getWeight() const;
    const std::string& getId() const;
};

// Functor for hashing containers based on id
struct HashContainer
{
    std::size_t operator()(const Container* _container) const {
        return std::hash<std::string>()(_container->getId());
    }
};


#endif //EX2_CONTAINER_H
