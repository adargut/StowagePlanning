#include "Utility.h"
#include "Container.h"
#include "Instruction.h"
#include "Error.h"
#include "Port.h"
#include "StowageAlgorithm.h"
#include "Simulation.h"

namespace Utility {
    bool fileAlreadyExists(const std::string &filename) {
        if (std::fstream(filename)) return true;
        return false;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }

    bool isNumber(const std::string &s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }

    bool readShipPlan(const std::string &travel_name, Plan &plan) {
        std::string filename;
        filename.append(travel_name);
        filename.append(BACKSLASH);
        filename.append(PLAN_FILE);
        ifstream in(filename);

        std::string line;
        if (!in.is_open()) {
            Error::throwErrorOpeningFile();
            return false;
        }
        bool first_line = true;
        int dim_z = 0, dim_y = 0, dim_x = 0;
        int x, y, z;

        while (std::getline(in, line)) {
            std::vector<std::string> validator = split(line, ' '); // For input validation
            if (validator.size() != 3) {
                Error::throwErrorReadingInput();
                return false;
            }
            std::stringstream ss(line);
            if (!isNumber(validator[0]) || !isNumber(validator[1]) || !isNumber(validator[2])) {
                Error::throwIncorrectFormatError();
                return false;
            }

            ss >> z >> y >> x;
            if (first_line) {
                first_line = false;
                dim_z = z;
                dim_y = y;
                dim_x = x;

                if (dim_x < 1 || dim_y < 1 || dim_z < 1) {
                    Error::throwSizeError();
                    return false;
                }
                plan = std::vector<std::vector<std::vector<std::string>>>
                        (z, std::vector<std::vector<std::string>>
                                (y, std::vector<std::string>(x, FREE_POS)));
            } else // Not the first line
            {
                if (x > dim_x - 1 || y > dim_y - 1 || z > dim_z || x < 0 || y < 0 || z < 1) {
                    Error::throwArrayBoundsError();
                    return false;
                }
                for (size_t i = 0; i < z; i++) {
                    plan[i][y][x] = ILLEGAL_POS;
                }
            }
        }
        in.close();
        return true;
    }

    bool readShipRoute(const std::string &travel_name, Route &route) {
        std::string filename;
        filename.append(travel_name);
        filename.append(BACKSLASH);
        filename.append(ROUTE_FILE);
        ifstream in(filename);
        if (!in.is_open()) {
            Error::throwErrorOpeningFile();
            return false;
        }

        std::string line;
        while (std::getline(in, line)) {
            std::vector<std::string> validator = split(line, ' '); // For input validation
            if (validator.size() != 1) {
                Error::throwIncorrectFormatError();
                return false;
            }
            route.push_back(line);
        }
        in.close();
        return true;
    }

    bool savePortInstructions(const Instructions &instructions, const std::string &algorithm_name,
                              const std::string &port_code, const std::string &travel_name)
    {
        if (port_code.empty() || algorithm_name.empty() || instructions.empty()) return false; // Input validation
        const std::string filename = port_code + CSV_SUFFIX;
        std::string curr_line;

        if (fileAlreadyExists(filename)) { // File for port exists, need to overwrite
            ifstream old_file(filename);
            ofstream new_file(TMP_FILE);
            if (!old_file || !new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }
            // Write header to new instructions file
            std::getline(old_file, curr_line);
            new_file << curr_line << std::endl;
            curr_line.clear();
            std::getline(old_file, curr_line);
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(travel_name);
            new_file << curr_line << std::endl;
            curr_line.clear();
            // Find right line with algorithm name
            bool found_line = false;
            while (std::getline(old_file, curr_line)) {
                if (split(curr_line, CSV_SEPERATOR[0])[0] == algorithm_name) {
                    found_line = true;
                    break;
                }
                new_file << curr_line << std::endl;
            }
            if (found_line) { // Algorithm line already in csv file, so just write new result to that line
                curr_line.append(Instruction::instructionsToString(instructions));
                new_file << curr_line << std::endl;
                while (std::getline(old_file, curr_line)) { // Write rest of the lines below line of algorithm found
                    new_file << curr_line << std::endl;
                }
            } else { // Algorithm not found, need to make new line corresponding to that algorithm
                curr_line.clear();
                curr_line.append(algorithm_name);
                // Write new set to instructions
                curr_line.append(Instruction::instructionsToString(instructions));
                new_file << curr_line << std::endl;
            }
            // Switch old file with new file
            old_file.close();
            new_file.close();
            remove(filename.c_str());
            rename(TMP_FILE, filename.c_str());
        }
        else { // File doesn't exist, need to create it
            ofstream new_file;
            new_file.open(filename);
            if (!new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }

            // Write header to new file instructions
            curr_line = "Port Instructions for port " + port_code;
            new_file << curr_line << std::endl;
            curr_line.clear();
            curr_line.append("Algorithm name");
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(travel_name);
            new_file << curr_line << std::endl;
            // Write algorithm line to new file
            curr_line = algorithm_name + Instruction::instructionsToString(instructions);
            new_file << curr_line << std::endl;
            new_file.close();
        }
        return true;
    }

    bool saveSimulation(std::string &string_to_write, const std::string &algorithm_name,
                        const std::string &travel_name, const std::string &filename) {
        if (string_to_write.empty() && filename == SIMULATION_ERRORS) { // No errors happened in algorithm run
            string_to_write = DEFAULT_ERROR;
        }
        std::string curr_line;
        if (fileAlreadyExists(filename)) { // Simulation file created already
            ifstream old_file(filename);
            ofstream new_file(TMP_FILE);
            if (!old_file || !new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }

            // Write new travel to header of csv file
            std::getline(old_file, curr_line);
            curr_line.append("\n");
            new_file << curr_line;
            curr_line.clear();
            std::getline(old_file, curr_line);
            curr_line.append(CSV_SEPERATOR + travel_name);
            curr_line.append("\n");
            new_file << curr_line;
            // Find right line with algorithm name
            bool found_line = false;

            while (std::getline(old_file, curr_line)) {
                if (split(curr_line, CSV_SEPERATOR[0])[0] == algorithm_name) {
                    found_line = true;
                    break;
                }
                new_file << curr_line << std::endl;
            }
            if (found_line) { // Algorithm line already in csv file, so just write new result to that line
                curr_line.append(CSV_SEPERATOR + string_to_write);
                new_file << curr_line << std::endl;
                while (std::getline(old_file, curr_line)) { // Write rest of the lines below line of algorithm found
                    new_file << curr_line << std::endl;
                }
            } else { // Algorithm not found, need to make new line corresponding to that algorithm
                curr_line.clear();
                curr_line.append(algorithm_name);
                curr_line.append(CSV_SEPERATOR);
                curr_line.append(string_to_write);
                new_file << curr_line << std::endl;
            }
            old_file.close();
            new_file.close();
            remove(filename.c_str());
            rename(TMP_FILE, filename.c_str());
        } else { // No simulation file exists, need to create it
            ofstream new_file;
            new_file.open(filename);
            if (!new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }

            // Write header of simulation file
            if (filename == SIMULATION_FILE) curr_line.append("Simulation results");
            else curr_line.append("Simulation errors");
            curr_line.append("\n");
            new_file << curr_line;
            curr_line.clear();
            curr_line.append("Algorithm name");
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(travel_name);
            new_file << curr_line << std::endl;
            // Write new algorithm line
            curr_line.clear();
            curr_line.append(algorithm_name);
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(string_to_write);
            new_file << curr_line << std::endl;
        }
        return true;
    }

    bool readPorts(const std::string &travel_name, Route &route, Ports &ports) {
        std::string curr_line;
        std::string curr_id;
        int curr_weight;
        std::string curr_destination;

        for (auto &port_code : route) {
            std::string filename;
            filename.append(travel_name);
            filename.append(BACKSLASH);
            filename.append(port_code);
            filename.append(CARGO_SUFFIX);

            ifstream in(filename);
            if (!in.is_open()) {
                Error::throwErrorOpeningFile();
                return false;
            }

            ContainersVector containers;
            while (std::getline(in, curr_line)) {
                std::stringstream ss(curr_line);
                ss >> curr_id >> curr_weight >> curr_destination;
                auto container = new Container(curr_weight, curr_destination, curr_id);
                containers.push_back(container);
            }
            Port port(port_code, containers);
            ports.push_back(port);
        }
        return true;
    }

    static void delete_containers(Ports& ports)
    {
        for (auto& port : ports)
        {
            for (auto& container : port.getContainersToLoad())
                delete container;
        }
    }

    bool start(const std::string &travel_name) {
        Plan plan;
        Route route;
        Ports ports;

        if (!Utility::readShipPlan(travel_name, plan)) {
            Error::throwErrorReadingInput();
            return false;
        }
        if (!Utility::readShipRoute(travel_name, route)) {
            Error::throwErrorReadingInput();
            return false;
        }
        if (!Utility::readPorts(travel_name,route, ports)) {
            Error::throwErrorReadingInput();
            return false;
        };
        StowageAlgorithm *algorithm = new NaiveStowageAlgorithm();
        WeightBalanceCalculator *calculator = new NaiveWeightBalanceCalculator();
        Simulation simulation(ports, plan, route, calculator, algorithm, travel_name);
        simulation.run_simulation();
        delete algorithm;
        delete calculator;
        delete_containers(ports);
        return true;
    }

    DistanceToDestinationComparator::DistanceToDestinationComparator(const int &currentPortIdx, const Route &route)
            : current_port_idx(currentPortIdx), route(route) {}

    bool DistanceToDestinationComparator::operator()(const Container *c1, const Container *c2) {
        return distance_to_destination(c1) < distance_to_destination(c2);
    }

    int DistanceToDestinationComparator::distance_to_destination(const Container *container) {
        for (int i = current_port_idx + 1; i < route.size(); i++) {
            if (route[i] == (container->getPortCode())) return (i - current_port_idx);
        }
        return INT_MAX; // Infinite
    }
}





