#include "Ship.h"
#include <fstream>
#include <iostream>
#include <sstream>

Ship::Ship(int _id) : id(_id) {}

bool Ship::readShipPlan(const std::string &path) //TODO: check input is valid
{
    ifstream in(path);
    std::string line;
    if (!in.is_open()) return false; //TODO: add error message
    bool first_line = true;
    int x, y, z;

    while (in >> line) {
        std::stringstream ss(line);
        if (first_line) {
            first_line = false;
            ss >> z >> x >> y;
            plan = std::vector(z, std::vector<std::vector<int>>(x, std::vector<int>(y, 0)));
        }
        ss >> x >> y >> z;
        for (size_t i = 0; i < z; i++) {
            plan[z][x][y] = -1;
        }
    }
    in.close();
    return true;
}

bool Ship::readShipRoute(const std::string &path) //TODO: check input is valid
{
    ifstream in(path);
    std::string line;
    if (!in.is_open()) return false; //TODO: add error message

    while (in >> line) {
        route.push_back(line);
    }
    in.close();
    return true;
}

void Ship::setWeightBalanceCalculator(WeightBalanceCalculator *_calculator) {
    calculator = _calculator;
}

const Plan &Ship::getPlan() const {
    return plan;
}

const Route &Ship::getRoute() const {
    return route;
}

bool Ship::loadContainer(int floor, int row, int col, const Container *const container_to_load) {
    if (plan[floor][row][col] != 0 || containers.count(id)) return false; // Position is occupied or container in ship
    int id = container_to_load->getId();
    updateContainerMap(floor, row, col, id, container_to_load);
    updatePlan(floor, row, col, id);
    return true;
}

const Container *const Ship::unloadContainer(int floor, int row, int col) {
    // TODO make this return error so we know why it failed
    if (plan[floor][row][col] <= 0) return nullptr; // Position is free or illegal
    const Container *const res = containers[plan[floor][row][col]].first;
    updateContainerMap(floor, row, col);
    updatePlan(floor, row, col, 0);
    return res;
}

void Ship::updatePlan(int floor, int row, int col, int val) {
    plan[floor][row][col] = val;
}

// Insert container to map
void Ship::updateContainerMap(int floor, int row, int col, int id, const Container *const container) {
    std::pair<const Container *const, Position> p(container, Position(floor, row, col));
    ContainerMap::value_type item(id, p);
    containers.insert(item); //TODO:: maybe emplace instead
}

// Remove container from map
void Ship::updateContainerMap(int floor, int row, int col) {
    containers.erase(plan[floor][row][col]);
}

Ship::~Ship() {
    delete calculator;
}