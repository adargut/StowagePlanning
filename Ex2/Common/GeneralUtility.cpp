//
// Created by adargut on 5/12/20.
//

#include "GeneralUtility.h"

void GeneralUtility::split(std::vector<string>& result, const string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) 
    {
        result.push_back(item);
    }
}

// trim from left
inline std::string& ltrim(std::string& s, const string t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const string t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const string t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}


void GeneralUtility::removeLeadingAndTrailingSpaces(std::vector<string> &split_line)
{
    for (size_t i = 0; i < split_line.size(); i++)
    {
        split_line[i] = trim(split_line[i]); 
    } 
}