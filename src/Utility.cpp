#include "Utility.h"
#include "Container.h"
namespace Utility {
    bool readShipPlan(const std::string &path, Plan& plan) //TODO: check input is valid
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

    bool readShipRoute(const std::string &path, Route& route) //TODO: check input is valid
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

    DistanceToDestinationComparator::DistanceToDestinationComparator(const int &currentPortIdx, const Route &route)
            : current_port_idx(currentPortIdx), route(route) {}

            bool DistanceToDestinationComparator::operator()(const Container * c1, const Container * c2) {
        return distance_to_destination(c1) < distance_to_destination(c2);
    }

    int DistanceToDestinationComparator::distance_to_destination(const Container *container) {
        int i = current_port_idx;
        for (; i < route.size(); i++) {
            if (route[i] == (container->getPortCode())) return (i - current_port_idx);
        }
        return std::numeric_limits<int>::infinity(); // Infinite
    }
}





