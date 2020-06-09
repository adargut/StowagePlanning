//
// Created by nir on 09/06/2020.
//

#ifndef EX3_ABSTRACTTASKSPRODUCER_H
#define EX3_ABSTRACTTASKSPRODUCER_H

#include "../common/GeneralUtility.h"

class AbstractTasksProducer
{
protected:
    const int numTasks = -1;
    std::atomic_int task_counter = 0;
    std::mutex m;

    std::optional<int> next_task_index() {
        for(int curr_counter = task_counter.load(); curr_counter < numTasks; ) {
            if(task_counter.compare_exchange_weak(curr_counter, curr_counter + 1)) {
                return {curr_counter};
            }
        }
        return {};
    }
public:
    AbstractTasksProducer(int numTasks): numTasks(numTasks) {}
    AbstractTasksProducer(AbstractTasksProducer&& other): numTasks(other.numTasks) {}
    virtual std::optional<std::function<void(void)>> getTask() = 0;
};


#endif //EX3_ABSTRACTTASKSPRODUCER_H
