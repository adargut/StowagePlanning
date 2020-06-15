
#include "SimulationTasksProducer.h"

std::optional<std::function<void(void)>> SimulationTasksProducer::getTask()
{
    auto task_index = next_task_index();
    if (task_index) {
        return [task_index, this]
        {
            // Initialize simulation parameters for current thread
            string algorithmName = m_processed_travels[*task_index].first;
            string travelName = m_processed_travels[*task_index].second.getTravelName();
            auto algorithm = AlgorithmManager::getInstance().getAlgorithmInstance(algorithmName);
            if (algorithm == nullptr) return; // algorithm didn't register
            Simulation simulation(std::move(algorithm), algorithmName, m_processed_travels[*task_index].second);

            // Thread done initializing, time to run simulation
            m.lock();
            std::cout << "\tRunning travel " << travelName
                      << " using algorithm " << algorithmName << " from thread"
                      << std::this_thread::get_id() << std::endl;
            m.unlock();
            simulation.initialize();
            std::string simulation_results = std::to_string(simulation.run());

            // Flush results into larger results map shared by all threads
            m.lock();
            if (!m_results.count(algorithmName)) m_results[algorithmName] = std::unordered_map<string, string>();
            m_results[algorithmName][travelName] = simulation_results;
            m.unlock();
        };
    }
    else return {};
}
