#include "OutputUtility.h"



bool OutputUtility::writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions)
{
    // TODO make sure instructions in right format
    ofstream write_file(output_full_path_and_file_name);
    if(!write_file.is_open()) 
    {
        std::cout << "Error opening cargo instructions\n";
        return false;   
    }
    string line;

    for (auto &instruction : instructions)
    {
        instruction.instructionToString(instruction, line);
        write_file << line << std::endl;
    }
    write_file.close();
    return true;
}

static bool sortBuffer(std::vector<string>& file_buffer)
{
    if (file_buffer.empty())
    {
        std::cout << "File buffer cannot be empty\n";
        return false;
    }
    auto cmp = [](string l1, string l2)
    {
        std::vector<string> split_l1, split_l2;
        GeneralUtility::removeSpaces(l1);
        GeneralUtility::removeSpaces(l2);
        GeneralUtility::split(split_l1, l1, DELIMETER);
        GeneralUtility::split(split_l2, l2, DELIMETER);

        int errors_1 = stoi(split_l1.back()), errors_2 = stoi(split_l2.back());
        // TODO check if the order is right:
        if (errors_2 < errors_1) return true; 
        if (errors_1 < errors_2) return false;
        else
        {
            int sum_1 = stoi(split_l1.end()[-2]), sum_2 = stoi(split_l2.end()[-2]);
            return sum_1 < sum_2; // TODO not sure about order? must check it..
        }        
    };
    std::sort(file_buffer.begin()+1, file_buffer.end(),cmp);
    return true;
}

static bool bufferToFile(const string &output_full_path_and_file_name, const std::vector<string>& file_buffer)
{
    ofstream write_file(output_full_path_and_file_name);
    if (!write_file.is_open())
    {
        std::cout << "Error opening file in buffer\n";
        return false;
    }
    for (auto& line : file_buffer)
    {
        write_file << line;
    }
    write_file.close();
    return true;
}

bool OutputUtility::writeResults(const string &output_full_path_and_file_name, AlgorithmTravelResultsMap &results,
                                 const std::vector<string> &travels_seen)
{
    std::vector<string> file_buffer;
    string header = RESULTS;

    // Write names of travels to first line
    for(auto& travel_seen : travels_seen)
    {
        header.append(travel_seen + CSV_SEPERATOR);
    }
    header.append(SUM);
    header.append(CSV_SEPERATOR);
    header.append(ERRORS);
    header.append("\n");
    file_buffer.push_back(std::move(header));

    // Write rest of data to simulation results
    for(auto& result_pair : results)
    {
        string line;
        int line_sum = 0;
        int line_errors = 0;
        line += result_pair.first + CSV_SEPERATOR;
        for (auto& numeric_result : results[result_pair.first])
        {
            if (line_sum < 0) line_errors += 1;
            else line_sum += std::stoi(numeric_result);
            line += numeric_result + CSV_SEPERATOR;
        }
        line += std::to_string(line_sum) + CSV_SEPERATOR;
        line += std::to_string(line_errors);
        line += "\n";
        file_buffer.push_back(std::move(line));
    }

    if (!sortBuffer(file_buffer)) return false;
    return bufferToFile(output_full_path_and_file_name, file_buffer);
}


bool OutputUtility::writeErrors(const string &output_full_path_and_file_name, AlgorithmTravelErrors &algorithm_errors,
                 const std::vector<string>& travels_seen)
{
    std::vector<string> file_buffer;
    string header = ERRORS_ALT;

    // Write names of travels to first line
    for(auto& travel_seen : travels_seen)
    {
        header.append(travel_seen + CSV_SEPERATOR);
    }
    header.pop_back();
    header += "\n";
    file_buffer.push_back(std::move(header));

    // Write rest of data to errors
    for(auto& result_pair : algorithm_errors)
    {
        string line;
        line += result_pair.first + CSV_SEPERATOR;
        for (auto &error_string : result_pair.second)
        {
            line += AlgorithmError::errorsToString(error_string) + CSV_SEPERATOR;
        }
        line.pop_back();
        line += "\n";
        file_buffer.push_back(std::move(line));
    }
    return bufferToFile(output_full_path_and_file_name, file_buffer);
}

