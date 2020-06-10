
#include "SimulationTasksProducer.h"

std::optional<std::function<void(void)>> SimulationTasksProducer::getTask()
{
    auto task_index = next_task_index();
    if (task_index) {
        return [task_index, this]
        { //TODO implement
            string algo_name = m_travel_data.first;
            string travelName = m_travel_data.second.getTravelName();
            auto algorithm = AlgorithmManager::getInstance().getAlgorithmInstance(algo_name);
            if (algorithm == nullptr) return; // algorithm didn't register

            Simulation simulation(std::move(algorithm), m_travel_data);
            simulation.initialize();

            m.lock();
            std::cout << "\tRunning travel " << travelName << " using algorithm " << algo_name << " from thread"
                << std::this_thread::get_id() << std::endl;
            m.unlock();
            m_results = simulation.run();
            // TODO put results in full vector single-threaded
            // TODO maybe check initialized properly?
//            resultsMap[algorithmName].push_back(std::to_string(simulation.run()));
//            Simulation simulation(algorithm, algo_name, m_travel_data);
//            Simulation simulation(std::move(algorithm), algorithmName, travelName, travel, outputPath);
//            simulation.initialize();
            // if(!resultsMap.count(algorithmName)) resultsMap[algorithmName] = std::vector<string>();
            // std::cout << "\tRunning travel " << travelName << " using algorithm " << algorithmName << std::endl;
            // resultsMap[algorithmName].push_back(std::to_string(simulation.run()));
            // std::cout << "\t\tFINISHED!\n";
        };
    }
    else return {};
}
