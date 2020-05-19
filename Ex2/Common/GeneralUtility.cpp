//
// Created by adargut on 5/12/20.
//

#include "GeneralUtility.h"

void GeneralUtility::split(std::vector<string>& result, const string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
}

void GeneralUtility::removeSpaces(string& input)
{
    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
}