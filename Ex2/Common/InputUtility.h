//
// Created by Adar on 10/05/2020.
//

#ifndef EX2_INPUTUTILITY_H
#define EX2_INPUTUTILITY_H

#include <algorithm>
#include <iostream>


namespace InputUtility {
    char* getCmdOption(char ** begin, char ** end, const std::string& option);
    bool cmdOptionExists(char** begin, char** end, const std::string& option);
}


#endif //EX2_INPUTUTILITY_H
