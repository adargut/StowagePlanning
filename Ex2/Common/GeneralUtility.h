//
// Created by adargut on 5/12/20.
//

#ifndef EX2_GENERALUTILITY_H
#define EX2_GENERALUTILITY_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "../Common/Container.h"

// typedef declarations
typedef typename std::vector<std::vector<std::vector<std::string>>> Plan;
// TODO should this be shared? not sure
typedef typename std::unordered_map<std::string, std::shared_ptr<Container>> PortContainers;
typedef typename std::vector<std::shared_ptr<Container>> ContainersVector;
typedef typename std::vector<std::string> Route;


namespace GeneralUtility
{
    //
}


#endif //EX2_GENERALUTILITY_H
