#include "Utility.h"
#include "Container.h"
#include "Instruction.h"
#include "Error.h"

namespace Utility {
    bool fileAlreadyExists(const std::string& filename)
    {
        if (std::fstream(filename)) return true;
        return false;
    }

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

    bool SavePortInstructions(const Instructions& instructions, const std::string& algorithm_name,
            const std::string& port_code)
    {
        if (port_code.empty() || algorithm_name.empty() || instructions.empty()) return false; // Input validation
        const std::string filename = port_code + CSV_PREFIX;
        std::string curr_line;

        if (!fileAlreadyExists(filename)) { // File for port exists, need to overwrite
            ifstream old_file(filename);
            ofstream new_file("tmp.txt");
            if(!old_file || !new_file)
            {
                Error::throwErrorOpeningFile();
                return false;
            }

            // Write header to new file
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

            // Write header to new file
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

    bool SaveSimulationResult(const std::string &path, int result) {
        ofstream simulation_results_file(path);
        if (!simulation_results_file.is_open()) return false; // TODO: appropriate error message


    }

    bool SaveSimulationErrors(const std::string &path, const AlgorithmErrors &errors) {
        return false;
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





