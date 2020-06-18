#include "Ship.h"

// Getter for ship route
const Route &Ship::getRoute() const
{
    return m_route;
}

// Setter for ship route
void Ship::setRoute(const Route &mRoute)
{
    m_route = mRoute;
}

// Getter for ship plan
const Plan &Ship::getPlan() const
{
    return m_plan;
}

// Setter for ship route
void Ship::setPlan(const Plan &mPlan)
{
    m_plan = mPlan;
}

// Getter for the index of the ship at the route
size_t Ship::getCurrentPortIdx() const
{
    return m_currentPortIdx;
}

// Getter for the map of the containers on ship
const ContainerMap &Ship::getContainerMap() const
{
    return m_containers;
}

// Checks if ship has a certain container on it
bool Ship::hasContainer(const string &container_id)
{
    return m_containers.count(container_id) > 0;
}

// Load a new container into the ship at position <floor, row, col>
bool Ship::loadContainer(int floor, int row, int col, std::shared_ptr<Container> container_to_load) {
    if (floor < 0 || row < 0 || col < 0 || floor > int(m_plan.size()) || row > int(m_plan[0].size()) ||
        col > int(m_plan[0][0].size())) {
        return false;
    }
    const std::string& id = container_to_load->getId();
    // Position is occupied or container in ship
    if (m_plan[floor][row][col] != FREE_POS || m_containers.count(id)) return false;
    if (floor != 0) {
        if (m_plan[floor - 1][row][col] == FREE_POS) return false; // Trying to place container "in the air"
    }
    if (floor != int(m_plan.size() - 1)) {
        if (m_plan[floor + 1][row][col] != FREE_POS) return false; // Trying to place container below an existing one
    }
    insertContainerMap(floor, row, col, container_to_load->getId(), container_to_load);
    updatePlan(floor, row, col, id);
    return true;
}

// Unload the container at <floor, row, col> from the ship
std::shared_ptr<Container> Ship::unloadContainer(int floor, int row, int col) {
    if (floor < 0 || row < 0 || col < 0 || floor > int(m_plan.size()) || row > int(m_plan[0].size()) ||
        col > int(m_plan[0][0].size())) {
        return nullptr;
    }
    if (m_plan[floor][row][col] == FREE_POS ||
        m_plan[floor][row][col] == ILLEGAL_POS) return nullptr; // Position is free or illegal
    if (floor != int(m_plan.size() - 1)) {
        if (m_plan[floor + 1][row][col] != FREE_POS) return nullptr; // There's a container above the container to unload
    }
    std::shared_ptr<Container> res = m_containers[m_plan[floor][row][col]].first;
    eraseContainerMap(floor, row, col);
    updatePlan(floor, row, col, std::string(FREE_POS));
    return res;
}

// Change the index of the ship at the route
void Ship::setCurrentPortIdx(int mCurrentPortIdx)
{
    m_currentPortIdx = mCurrentPortIdx;
}

// Advance the ship's index by one to next port in route
void Ship::advanceCurrentPortIdx() {
    m_currentPortIdx++;
}

// Checks if the ship is full
bool Ship::isShipFull() 
{
    for (int z = 0; z < int(m_plan.size()); z++) 
    {
        for (int y = 0; y < int(m_plan[0].size()); y++) 
        {
            for (int x = 0; x < int(m_plan[0][0].size()); x++) 
            {
                if(m_plan[z][y][x] == FREE_POS) return false;
            }
        }
    }
    return true;
}

// Updates the plan of the ship with a new ID
void Ship::updatePlan(int floor, int row, int col, const std::string& val) 
{
    m_plan[floor][row][col] = val;
}

// Insert container to ship's map
void Ship::insertContainerMap(int floor, int row, int col, const std::string& id, std::shared_ptr<Container> container) 
{
    std::pair<std::shared_ptr<Container>, Position> p(container, Position{floor, row, col});
    ContainerMap::value_type item(id, p);
    m_containers.insert(item);
}

// Remove container from map
void Ship::eraseContainerMap(int floor, int row, int col) 
{
    m_containers.erase(m_plan[floor][row][col]);
}

bool Ship::findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y)
{
    for (int z = 0; z < int(m_plan.size()); z++)
    {
        for (int y = 0; y < int(m_plan[0].size()); y++)
        {
            for (int x = 0; x < int(m_plan[0][0].size()); x++)
            {
                // Ignore unwanted free positions
                if (illegal_x_y.has_value() && illegal_x_y->first == x && illegal_x_y->second == y) continue;
                if (m_plan[z][y][x] == FREE_POS)
                {
                    res_x = x;
                    res_y = y;
                    res_z = z;
                    return true;
                }
            }
        }
    }
    return false;
}

int Ship::countFreePos()
{
    int free_positions = 0;

    for (int z = 0; z < int(m_plan.size()); z++)
    {
        for (int y = 0; y < int(m_plan[0].size()); y++)
        {
            for (int x = 0; x < int(m_plan[0][0].size()); x++)
            {
                if (m_plan[z][y][x] == FREE_POS)
                {
                    free_positions++;
                }
            }
        }
    }
    return free_positions;
}
