//
// Created by Adar on 10/05/2020.
//

#include "InputUtility.h"

bool InputUtility::cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

char *InputUtility::getCmdOption(char **begin, char **end, const std::string &option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}