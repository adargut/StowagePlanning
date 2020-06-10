
#include "SimulationTasksProducer.h"

std::optional<std::function<void(void)>> SimulationTasksProducer::getTask()
{
    auto task_index = next_task_index();
    if (task_index) {
        return [task_index, this]
        {
            // Initialize simulation parameters for current thread
            string algorithmName = m_processed_travels[*task_index].first;
            auto algorithm = AlgorithmManager::getInstance().getAlgorithmInstance(algorithmName);
            if (algorithm == nullptr) return; // algorithm didn't register
            Simulation simulation(std::move(algorithm), m_processed_travels[*task_index]);

            // Thread done initializing, time to run simulation
            m.lock();
            std::cout << "\tRunning travel " << m_processed_travels[*task_index].second.getTravelName()
                      << " using algorithm " << algorithmName << " from thread"
                      << std::this_thread::get_id() << std::endl;
            m.unlock();
            int simulation_results = simulation.run();

            // Flush results into larger results map shared by all threads
            m.lock();
            m_results[algorithmName].push_back(std::to_string(simulation_results));
            m.unlock();

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
