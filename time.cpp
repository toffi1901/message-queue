#include <string>
#include <ctime>
#include <vector>

#include "message.h"

/*!
 * @brief Turns the string into time point
 * @param input the time string
 * @param time
 * @return true if it isn`t failed input, else false
 */

std::chrono::system_clock::time_point input_time(std::istream &in)
{
    std::string str_time;
    std::getline(in, str_time);
    if (check_input(in) == false)
        in.setstate(std::ios::failbit);
    if (str_time.empty())
        return system_clock::now();
    std::tm tm = {};
    std::istringstream iss(str_time);
    iss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    if (iss.bad())
    {
        iss.clear();
        throw std::runtime_error("Bad input");
    }
    if (iss.fail())
    {
        iss.clear();
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Incorrect input");
    }
    return system_clock::from_time_t(std::mktime(&tm));
}

bool parse_time(const std::string &input, std::chrono::system_clock::time_point &time)
{
    std::istringstream iss(input);
    std::tm tm = {};
    iss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    if (iss.fail())
    {
        return false;
    }
    std::time_t tt = std::mktime(&tm);
    time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return true;
}

/*!
 * @brief Separating string into tokens
 * @param str the string for separating
 * @param delim
 * @return vector of tokens
 */

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tok;
    std::string::size_type start = 0;
    std::string::size_type end = str.find_first_of(delim, start);
    while (end != std::string::npos)
    {
        if (end != start)
        {
            tok.push_back(str.substr(start, end - start));
        }
        start = end + 1;
        end = str.find_first_of(delim, start);
    }
    if (start < str.length())
    {
        tok.push_back(str.substr(start));
    }
    return tok;
}
