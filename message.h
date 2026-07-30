#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>
#include <vector>
#include <compare>
#include <chrono>

using namespace std::chrono;
using namespace std::literals::chrono_literals;

class Message
{
private:
    std::string message;
    std::string chat;
    time_point<system_clock> time;

public:
    Message();
    Message(const std::string &pre_message, const std::string &chat_name, time_point<system_clock> time_msg);
    Message(const std::string &pre_message, const std::string &chat_name);

    void set_message(const std::string &pre_message);
    void set_chat(const std::string &chat_name);
    void set_time(time_point<system_clock> time_msg);

    /*!
     * @brief function which get message
     * @return a string with a message
     */
    const std::string &get_message() const { return message; }

    /*!
     * @brief function which get name of chat
     * @return a string with a name of chat
     */
    const std::string &get_chat() const { return chat; }

    /*!
     * @brief function which get time
     * @return time of sending message
     */
    time_point<system_clock> get_timeline() const { return time; }

    friend std::istream &operator>>(std::istream &in, Message &msg);
    friend std::ostream &operator<<(std::ostream &out, const Message &msg);

    Message add(const Message &rhs) const;
    std::weak_ordering operator<=>(const Message &rhs) const;
    bool find_word(const std::string &word) const;

    void output_message();
    void input_message();
};

std::chrono::system_clock::time_point input_time(std::istream &in);
time_point<system_clock> input_time(std::istream &in);
bool parse_time(const std::string &input, std::chrono::system_clock::time_point &time);
bool getint(std::istream &in, int &option, int l, int r);

std::vector<std::string> split(const std::string &str, const std::string &delim);
bool check_input(std::istream &in);
bool check_input(std::string &string);

#endif