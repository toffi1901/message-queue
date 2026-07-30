#include <iostream>
#include <limits>
#include <numeric>
#include <ctime>
#include <cstring>
#include "queue.h"

/*time_point<system_clock> input_time(std::istream &in)
{
    time_point<system_clock> time;
    std::string input;
    while (true)
    {
        std::cout << "Input time using format Y.M.D H.M: " << std::endl;
        check_input(in, input);
        if (input.empty())
        {
            return system_clock::now();
        }
        if (parse_time(input, time))
        {
            return time;
        }
        std::cout << "Invalid format of time. Please try again." << std::endl;
    }
    return time;
}*/

/*!
 * @brief function for input Message
 */

void Message::input_message()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Input message chat option(message, chat_name, time(optional)): " << std::endl;
    std::cin >> *this;
}

/*!
 * @brief function for output Message
 */

void Message::output_message()
{
    std::cout << "The text of message The chat Time of sending" << std::endl;
    std::cout << *this;
}

/*!
 * @brief function for output Queue
 */

void Queue::input_queue()
{
    std::cout << "Input count of messages" << std::endl;
    std::cout << "Input message chat option(message, chat_name, time(optional)): " << std::endl;
    std::cin >> *this;
}
