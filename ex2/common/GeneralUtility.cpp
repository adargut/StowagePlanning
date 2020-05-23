#include "GeneralUtility.h"

// Split string by delimeter, stores outpit in result
void GeneralUtility::split(std::vector<string>& result, const string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) 
    {
        result.push_back(item);
    }
}

// Trim whitespaces from the left
void ltrim(std::string& s, const string t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
}

// Trim whitespaces from right
void rtrim(std::string& s, const string t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
}

// Trim whitespaces from left & right
void GeneralUtility::trim(std::string& s, const string t)
{
    rtrim(s, t);
    ltrim(s, t);
}

// Trim all whitespaces from vector of strings
void GeneralUtility::removeLeadingAndTrailingSpaces(std::vector<string> &split_line)
{
    for (size_t i = 0; i < split_line.size(); i++)
    {
        trim(split_line[i]); 
    } 
}