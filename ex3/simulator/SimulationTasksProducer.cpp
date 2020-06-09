//
// Created by nir on 09/06/2020.
//

#include "SimulationTasksProducer.h"

std::optional<std::function<void(void)>> SimulationTasksProducer::getTask()
{
    auto task_index = next_task_index();
    if(task_index) {
        return [task_index, this]{ //TODO implement
            m.lock();
            // std::cout << std::this_thread::get_id() << "- just wrote: " << m_tasks[*task_index] << " at index : " << *task_index << std::endl;
            m.unlock();
            m_results[*task_index] = m_algo_travel_pairs[*task_index] + m_algo_travel_pairs[*task_index]; // store entire travel data, like errors and plan etc.. not just name (in real code)
            std::this_thread::yield(); // just to check threads switch
        };
    }
    else return {};
}
