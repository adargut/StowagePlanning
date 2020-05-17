#include "OutputUtility.h"



bool OutputUtility::writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions)
{
    // TODO make sure instructions in right format
    // TODO what if file already exists?? delete it or write to it??
    ofstream write_file(output_full_path_and_file_name);
    write_file.open(output_full_path_and_file_name, std::ios::app);
    string line;

    for (auto &instruction : instructions)
    {
        // TODO maybe make this non static member function?
        instruction.instructionToString(instruction, line);
        write_file << line << std::endl;;
    }
    write_file.close();
}

int findAlgorithmRow(const string &algorithm_name, const string &output_full_path_and_file_name)
{
    ifstream read_file(output_full_path_and_file_name);
    string line;
    int idx = 0;

    while (std::getline(read_file, line))
    {
        std::vector<string> split_line;
        boost::algorithm::split(split_line, line, boost::is_any_of(CSV_SEPERATOR));
        if (split_line[0] == algorithm_name) return idx;
        ++idx;
    }
    return -1;
}

int findTravelCol(const string &travel_name, const string &first_line)
{
    std::vector<string> split_line;
    boost::algorithm::split(split_line, first_line, boost::is_any_of(CSV_SEPERATOR));

    for (int i = 0; i < split_line.size(); i++)
    {
        if (split_line[i] == travel_name) return i;
    }
    return -1;
}

string updateSumForLine(string line, int sum_idx)
{
    int total_sum = 0;
    std::vector<string> split_line;
    boost::algorithm::split(split_line, line, boost::is_any_of(CSV_SEPERATOR));
    string so_far = split_line[0];

    for (int i = 1; i < sum_idx; i++)
    {
        so_far += split_line[i] + CSV_SEPERATOR;
        total_sum += std::stoi(split_line[i]);
    }
    so_far.append(std::to_string(total_sum) + CSV_SEPERATOR);
    for (int i = sum_idx; i < split_line.size(); i++)
    {
        if (i == split_line.size() - 1) so_far += split_line[i] + CSV_SEPERATOR;
        else so_far += split_line[i];
    }
    return so_far;
}

string updateErrorsForLine(string line, int error_idx)
{
    int total_errors = 0;
    std::vector<string> split_line;
    boost::algorithm::split(split_line, line, boost::is_any_of(CSV_SEPERATOR));
    string so_far = split_line[0];

    for (int i = 1; i < error_idx; i++)
    {
        so_far += split_line[i] + CSV_SEPERATOR;
        if (split_line[i] == "-1") total_errors += 1;
    }
    so_far.append(std::to_string(total_errors) + CSV_SEPERATOR);
    for (int i = error_idx; i < split_line.size(); i++)
    {
        if (i == split_line.size() - 1) so_far += split_line[i] + CSV_SEPERATOR;
        else so_far += split_line[i];
    }
    return so_far;
}

string writeNewTravel(const string& line, const string &travel_name, bool first_line, int travel_idx=-1, string results="0")
{
    std::vector<string> split_line;
    boost::algorithm::split(split_line, line, boost::is_any_of(CSV_SEPERATOR));
    string so_far;

    if (first_line)
    {
        int last = 0;
        for (int i = 0; i < split_line.size(); i++)
        {
            if (split_line[i] == SUM)
            {
                last = i;
                break;
            }
            else
            {
                so_far += split_line[i] + CSV_SEPERATOR;
            }
        }
        so_far += travel_name + CSV_SEPERATOR;
        for (int i = last; i < split_line.size(); i++)
        {
            if (i == split_line.size() - 1) so_far += split_line[i] + CSV_SEPERATOR;
            else so_far += split_line[i];
        }
    }
    else
    {
        for (int i = 0; i < travel_idx; i++)
        {
            so_far += split_line[i] + CSV_SEPERATOR;
        }
        so_far += "0"; // TODO should we really write 0 when writing a new travel??
        so_far += CSV_SEPERATOR;
        for (int i = travel_idx; i < split_line.size(); i++)
        {
            so_far += split_line[i];
        }
    }
    return so_far;
}

bool OutputUtility::writeSimulationResults(const string &output_full_path_and_file_name, const string &travel_name, const string &algorithm_name, 
                                           int num_errors, int total_operations) 
{
    ofstream write_file(output_full_path_and_file_name);
    // Need to create results
    if (!fs::exists(output_full_path_and_file_name))
    {
        write_file.open(output_full_path_and_file_name, std::ios::app);
        // First line
        string header = RESULTS + travel_name + CSV_SEPERATOR + SUM + CSV_SEPERATOR + ERRORS;
        write_file << header << std::endl;
        // Second line
        header = algorithm_name + CSV_SEPERATOR + std::to_string(total_operations) + CSV_SEPERATOR 
                                + std::to_string(total_operations) + CSV_SEPERATOR + std::to_string(num_errors);
        write_file << header << std::endl;
    }
    // Results already exist
    else
    {
        ifstream old_file(output_full_path_and_file_name);
        int idx = 0;
        int correct_idx = findAlgorithmRow(algorithm_name, output_full_path_and_file_name);
        int travel_idx = -1;
        string line;
        string first_line;
        bool is_first_line = true;

        while (std::getline(old_file, line))
        {
            if (is_first_line)
            {
                string new_header = writeNewTravel(line, travel_name, true);
                write_file << new_header << std::endl;
                first_line = new_header;
                travel_idx = findTravelCol(travel_name, first_line);
                is_first_line = false;
            }
            // Found correct row for algorithm
            else if (idx == correct_idx)
            {
                string replaced_line = writeNewTravel(line, travel_name, false, travel_idx, std::to_string(total_operations));
                write_file << replaced_line << std::endl;
            }
            // Incorrect line for algorithm, not first line
            else
            {
                string replaced_line = writeNewTravel(line, travel_name, false, travel_idx);
                write_file << replaced_line << std::endl;
            }
            idx++;
        }
    }
    
}
