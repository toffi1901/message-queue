#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>
#include <compare>

#include "message.h"

/*!
 * @brief Default constructor
 */

Message::Message() {}

/*!
 * @brief Initialize a Message with custom input that includes time
 * @param pre_message The string with message user input
 * @param chat_name The string with chat name user input
 * @param time_msg The time user input
 */

Message::Message(const std::string &pre_message, const std::string &chat_name, time_point<system_clock> time_msg)
{
    message = pre_message;
    chat = chat_name;
    time = time_msg;
}

/*!
 * @brief Initialize a Message with custom input
 * @param pre_message The string with message user input
 * @param chat_name The string with chat name user input
 */

Message::Message(const std::string &pre_message, const std::string &chat_name)
{
    message = pre_message;
    chat = chat_name;
    time = std::chrono::system_clock::now();
}

/*!
 * @brief Set a message in Message
 * @param msg A string with a message that is assigned to a class element
 */

void Message::set_message(const std::string &msg)
{
    message = msg;
}

/*!
 * @brief Set a chat_name in Message
 * @param chat_name A string with a chat_name that is assigned to a class element
 */

void Message::set_chat(const std::string &chat_name)
{
    chat = chat_name;
}

/*!
 * @brief Set a send_time of Message
 * @param send_time A time_point when the message was sent
 */

void Message::set_time(time_point<system_clock> send_time)
{
    time = send_time;
}

/*!
 * @brief operator which adds values
 *
 * @param rhs the second operand
 * @throws std::runtime_error() if chats aren`t equal.
 * @return New instance of the class
 */

Message Message::add(const Message &rhs) const
{
    if (this->get_chat() != rhs.get_chat())
    {
        throw std::runtime_error("Chats aren`t equal!");
    }
    auto &min = this->get_timeline() < rhs.get_timeline() ? *this : rhs;
    auto &max = this->get_timeline() > rhs.get_timeline() ? *this : rhs;
    return Message(min.message + max.message, rhs.get_chat(), max.get_timeline());
}

/*!
 * @brief equalness operator
 *
 * @param rhs the second operand
 * @return equalness of elements by chat names and sending time.
 */

std::weak_ordering Message::operator<=>(const Message &rhs) const
{
    return std::tie(chat, time) <=> std::tie(rhs.chat, rhs.time);
}

/*!
 * @brief find message by word
 *
 * @param word the string with word which message is being searched for.
 * @return true if the message was found, false if it`s not.
 */

bool Message::find_word(const std::string &word) const
{
    std::vector<std::string> tok = split(this->get_message(), " .,!?(){}");
    auto result = std::find(tok.begin(), tok.end(), word);
    return result != tok.end();
}

/*!
 * @brief input Message operator
 *
 * @param in the input stream.
 * @param msg input Message.
 * @return the input stream.
 */

std::istream &operator>>(std::istream &in, Message &msg)
{
    std::string message;
    std::string chat;
    time_point<system_clock> time;
    std::getline(in, message);
    if (check_input(in) == false)
        return in;
    std::getline(in, chat);
    if (check_input(in) == false)
        return in;
    time = input_time(in);
    msg.message = message;
    msg.chat = chat;
    msg.time = time;
    return in;
}

/*!
 * @brief output Message operator
 *
 * @param out the output stream.
 * @param msg output Message.
 * @return the output stream.
 */

std::ostream &operator<<(std::ostream &out, const Message &msg)
{
    return out << std::format("{} {} {:%d.%m.%Y %H:%M}\n", msg.get_message(), msg.get_chat(), msg.get_timeline());
}
