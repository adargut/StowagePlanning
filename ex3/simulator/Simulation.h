#ifndef EX2_SIMULATION_H
#define EX2_SIMULATION_H

#include "../common/AbstractAlgorithm.h"
#include "../common/Ship.h"
#include "../common/Port.h"
#include "../common/GeneralUtility.h"
#include "../common/InputUtility.h"
#include "../common/Instruction.h"
#include "../common/DistanceToDestinationComparator.h"
#include "../common/WeightBalanceCalculator.h"
#include "../common/OutputUtility.h"
#include "TravelData.h"
#include <memory>
#include "Error.h"

/**
 * @brief Simulation.h runs a simulation of the algorithm provides in the .so file
 * 
 */
class Simulation {
    // TODO add member for slot position
    // TODO add static global member to determine which travels were initialized
    std::unique_ptr<AbstractAlgorithm> m_algorithm;
    std::vector<AlgorithmError> m_algorithmErrors;
    const string m_algorithmName;
    const ProcessedDataSingleton &m_travel_data;
    Ship m_ship;
    Ports m_ports;
    bool m_canRun = true;
public:
    Simulation(std::unique_ptr<AbstractAlgorithm> algorithm, const ProcessedDataSingleton &travel_data) :
            m_algorithm(std::move(algorithm)), m_algorithmName(std::move(travel_data.first)),
            m_travel_data(travel_data) , m_ports(std::move(travel_data.second.getPorts())) {};
    // Return false if run can't be started
    bool initialize();
    int run();
private:
    bool isDestinationReachable(std::shared_ptr<const Container> container);
    void handleUnloadOperation(Port &port, const Instruction &instruction, Errors &errors);
    void handleLoadOperation(Port &port, const Instruction &instruction, Errors &errors);
    void handleMoveOperation(const Instruction &instruction, Errors &errors);
    void handleRejectOperation(Port &port, const Instruction &instruction, Errors &errors,
                               std::vector<string> &rejected);
    void checkContainersForgottenOnShip(Port& port, Errors& errors);
    static void checkContainersLeftOnPort(Port &port, PortContainers& original_containers, Errors& errors);
    static void checkUnloadedRejected(PortContainers& unloaded_containers,
            std::vector<std::string>& rejected, Errors& errors);
    void checkLatestDestinationsRejected(Port& port, PortContainers& unloaded_containers, DistanceToDestinationComparator& distance_to_dest,
                                         Errors& errors);
    void checkNoRoomForContainers(PortContainers& unloaded_containers, DistanceToDestinationComparator& distance_to_dest,
                                  Errors& errors);
    static void setRealDestinations(const Route& route, int curr_idx, ContainersVector& containers);
};
#endif //EX2_SIMULATION_H
