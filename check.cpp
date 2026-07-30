#include <iostream>
#include <limits>
#include <numeric>
#include <ctime>
#include <regex>

#include "message.h"

/*!
 * @brief Checks the correctness of input using istream.
 *
 * @param inputt The string to check.
 * @throws std::runtime_error() if std::cin.bad() or std::cin.eof().
 */

bool check_input(std::istream &in)
{
    if (in.bad())
    {
        in.clear();
        throw std::runtime_error("Bad input");
    }
    if (in.eof())
    {
        in.clear();
        throw std::runtime_error("Broken input");
    }
    if (in.fail())
    {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

/*!
 * @brief Checks the correctness of string input
 *
 * @param string The string to check.
 * @throws std::runtime_error() if std::cin.bad() or std::cin.eof().
 */

bool check_input(std::string &string)
{
    std::getline(std::cin, string);
    if (std::cin.bad())
    {
        std::cin.clear();
        throw std::runtime_error("Input error\n");
    }
    if (std::cin.eof())
    {
        std::cin.clear();
        throw std::runtime_error("Input error\n");
    }
    while (std::cin.fail())
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, string);
    }
    return true;
}

/*!
 * @brief Checks the correctness of int input using istream
 *
 * @param option The string to check.
 * @param l left border.
 * @param r right border.
 * @throws std::runtime_error() if std::cin.bad() or std::cin.eof().
 */

bool getint(std::istream &in, int &option, int l, int r)
{
    in >> option;
    if (in.eof())
    {
        throw std::runtime_error("Broken input");
    }
    if (in.bad())
    {
        in.clear();
        throw std::runtime_error("Broken input");
    }

    while (in.fail())
    {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in >> option;
    }
    while (option > r || option < l)
    {
        in >> option;
    }
    return true;
}
