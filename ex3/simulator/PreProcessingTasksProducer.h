//
// Created by nir on 09/06/2020.
//

#ifndef EX3_PREPROCESSINGTASKSPRODUCER_H
#define EX3_PREPROCESSINGTASKSPRODUCER_H

#include "AbstractTasksProducer.h"
#include "../common/InputUtility.h"

class PreProcessingTasksProducer : public AbstractTasksProducer
{
    const string m_travels_dir;
    std::vector<string> &m_travel_paths;
    std::vector<TravelData> &m_travels_data;
public:
    PreProcessingTasksProducer(int numTasks, string travels_dir, std::vector<string> &paths, std::vector<TravelData> &travels_data) :
        AbstractTasksProducer(numTasks), m_travels_dir(std::move(travels_dir)), m_travel_paths(paths), m_travels_data(travels_data) {}

    PreProcessingTasksProducer(PreProcessingTasksProducer && other):
        AbstractTasksProducer(std::move(other)), m_travels_dir(std::move(other.m_travels_dir)), m_travel_paths(other.m_travel_paths),
                                                            m_travels_data(other.m_travels_data) {}

    std::optional<std::function<void(void)>> getTask() override;
};


#endif //EX3_PREPROCESSINGTASKSPRODUCER_H
