#include "Utility.h"
#include "Container.h"
#include "Instruction.h"
#include "Error.h"
#include "Port.h"

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

    bool readShipPlan(const std::string &path, Plan &plan) //TODO: check input is valid
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

    bool SavePortInstructions(const Instructions &instructions, const std::string &algorithm_name,
                              const std::string &port_code)
    {
        if (port_code.empty() || algorithm_name.empty() || instructions.empty()) return false; // Input validation
        const std::string filename = port_code + CSV_PREFIX;
        std::string curr_line;

        if (fileAlreadyExists(filename)) { // File for port exists, need to overwrite
            ifstream old_file(filename);
            ofstream new_file("tmp.txt");
            if (!old_file || !new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }
            // Write header to new instructions file
            old_file >> curr_line;
            new_file << curr_line << std::endl;
            curr_line.clear();
            // Write algorithms row to new file
            old_file >> curr_line;
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(algorithm_name);
            new_file << curr_line << std::endl;
            curr_line.clear();
            // Write new set of instructions
            old_file >> curr_line;
            curr_line.append(CSV_SEPERATOR);
            curr_line.append(Instruction::instructionsToString(instructions));
            // Switch old file with new file
            old_file.close();
            remove(filename.c_str());
            rename("tmp.txt", filename.c_str());
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
            // Write algorithm line to new file
            curr_line = "Algorithm " + algorithm_name;
            new_file << curr_line << std::endl;
            // Write set of instructions to new file
            curr_line = Instruction::instructionsToString(instructions);
            new_file << curr_line << std::endl;
            new_file.close();
        }
        return true;
    }

    bool saveSimulation(const std::string &string_to_write, const std::string &algorithm_name,
                        const std::string &travel_name, const std::string &filename) {
        std::string curr_line;
        if (fileAlreadyExists(filename)) { // Simulation file created already
            ifstream old_file(filename);
            ofstream new_file("tmp.txt");
            if (!old_file || !new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }

            // Write new travel to header of csv file
            old_file >> curr_line;
            curr_line.append(travel_name);
            curr_line.clear();
            // Find right line with algorithm name
            bool found_line = false;
            while (old_file >> curr_line) {
                if (split(curr_line, CSV_SEPERATOR[0])[0] == algorithm_name) {
                    found_line = true;
                    break;
                }
                new_file << curr_line << std::endl;
            }
            if (found_line) { // Algorithm line already in csv file, so just write new result to that line
                curr_line.append(string_to_write);
                new_file << curr_line << std::endl;
                while (old_file >> curr_line) { // Write rest of the lines below line of algorithm found
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
            remove(filename.c_str());
            rename("tmp.txt", filename.c_str());
        } else { // No simulation file exists, need to create it
            ofstream new_file;
            new_file.open(filename);
            if (!new_file) {
                Error::throwErrorOpeningFile();
                return false;
            }
            // Write header of simulation file
            if (filename == SIMULATION_FILE) curr_line.append("SIMULATION RESULTS");
            else curr_line.append("SIMULATION ERRORS");
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

    bool readPorts(Route &route, Ports &ports) {
        for (auto &port : ports) {
            route.push_back(port.getCode());
        }
    }

    DistanceToDestinationComparator::DistanceToDestinationComparator(const int &currentPortIdx, const Route &route)
            : current_port_idx(currentPortIdx), route(route) {}

    bool DistanceToDestinationComparator::operator()(const Container *c1, const Container *c2) {
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





