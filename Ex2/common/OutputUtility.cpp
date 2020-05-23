#include "OutputUtility.h"

// Write instructions for cargo to file
bool OutputUtility::writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions)
{
    ofstream write_file(output_full_path_and_file_name);
    if(!write_file.is_open()) 
    {
        return false;   
    }
    string line;

    for (auto &instruction : instructions)
    {
        Instruction::instructionToString(instruction, line);
        write_file << line << std::endl;
    }
    write_file.close();
    return true;
}

// Sorts rows based on num errors, tiebreaking by number of operations
static bool sortBuffer(std::vector<string>& file_buffer)
{
    if (file_buffer.empty())
    {
        return false;
    }
    // Custom comparator
    auto cmp = [](string l1, string l2)
    {
        std::vector<string> split_l1, split_l2;
        GeneralUtility::split(split_l1, l1, DELIMETER);
        GeneralUtility::removeLeadingAndTrailingSpaces(split_l1);
        GeneralUtility::split(split_l2, l2, DELIMETER);
        GeneralUtility::removeLeadingAndTrailingSpaces(split_l2);

        int errors_1 = stoi(split_l1.back()), errors_2 = stoi(split_l2.back());
        if (errors_2 < errors_1) return false;
        if (errors_1 < errors_2) return true;
        else
        {
            int sum_1 = stoi(split_l1.end()[-2]), sum_2 = stoi(split_l2.end()[-2]);
            return sum_1 < sum_2;
        }        
    };

    std::sort(file_buffer.begin()+1, file_buffer.end(),cmp);
    return true;
}

// Pours buffer of rows corresponding to an entire program run into a file
static bool bufferToFile(const string &output_full_path_and_file_name, const std::vector<string>& file_buffer)
{
    ofstream write_file(output_full_path_and_file_name);
    if (!write_file.is_open())
    {
        return false;
    }
    for (auto& line : file_buffer)
    {
        write_file << line;
    }

    write_file.close();
    return true;
}

// Writes simulation results into a file
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
            if (std::stoi(numeric_result) < 0) 
            {
                line_errors += 1;
            }
            else 
            {
                line_sum += std::stoi(numeric_result);
            }
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

// Writes errors detected by simulation or general input errors into errors file
bool OutputUtility::writeErrors(const string &output_full_path_and_file_name, std::vector<Error> &algorithm_errors)
{
    if (algorithm_errors.empty()) return true; // No errors to report
    fs::path p(output_full_path_and_file_name);
    fs::create_directories(p.parent_path());

    ofstream write_file(output_full_path_and_file_name);
    if(!write_file.is_open()) 
    {
        return false;   
    }

    // Write header to make file look nicer
    string header;
    if (p.extension() == SIMULATION_ERRORS_SUFFIX)
    {
        header = "The following errors were reported by the simulation:\n";
    }
    else
    {
        header = "The following general errors were found:\n";
    }
    write_file << header;
    write_file << LINE_SEPERATOR;

    for (auto &error : algorithm_errors)
    {
        write_file << "\t" + error.errorToString() << std::endl;
    }

    write_file.close();
    return true;
}

// Writes errors detected by algorithm into a file
bool OutputUtility::writeAlgorithmErrors(const string &output_full_path_and_file_name, std::vector<AlgorithmError> &errors)
{
    if (errors.empty()) return true; // No errors to report
    fs::path p(output_full_path_and_file_name);
    fs::create_directories(p.parent_path());
    ofstream write_file(output_full_path_and_file_name);
    if(!write_file.is_open()) 
    {
        return false;   
    }

    // Write header to make file look nicer
    string header = "The following errors were reported by the algorithm:\n";
    write_file << header;
    write_file << LINE_SEPERATOR;

    for (auto &error : errors)
    {
        write_file << "\t" + error.errorToString() << std::endl;
    }
    
    write_file.close();
    return true;
}
