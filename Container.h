#ifndef EX1_CONTAINER_H
#define EX1_CONTAINER_H

#include <vector>
#include <string>

class Container {
private:
    std::string port_code;
    int id;
    int weight;
public:
    int getWeight() const;
    const std::string& getPortCode() const;
    int getId() const;
};


#endif //EX1_CONTAINER_H
