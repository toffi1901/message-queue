#include <algorithm>
#include <numeric>
#include <vector>
#include "queue.h"
#include <iostream>

/*!
 * @brief function which rotate queue
 * @return n elements from queue
 */

auto Queue::get_queue_range()
{
    auto rotated_range = std::ranges::subrange(chats, chats + max_size);
    std::ranges::rotate(rotated_range, rotated_range.begin() + head);
    return std::ranges::subrange(rotated_range.begin(), rotated_range.begin() + size);
}

/*!
 * @brief function which change size, if queue is full
 *
 * @param new_size new size
 * @throws std::runtime_error() if new size < size.
 */

void Queue::resize(int new_size)
{
    if (new_size < size)
    {
        throw std::runtime_error("New size is too small");
    }
    if (this->check_queue() != FULL)
    {
        throw std::runtime_error("Not full queue");
    }
    Message *new_chats = new Message[new_size];
    try
    {
        auto view = get_queue_range();
        std::move(view.begin(), view.end(), new_chats);
        delete[] chats;
        max_size = new_size;
        chats = new_chats;
        tail = size;
        head = 0;
    }
    catch (const std::exception &e)
    {
        delete[] new_chats;
        throw;
    }
}

/*!
 * @brief function of getting head
 * @return queue head
 */

int Queue::get_head() const
{
    return head;
}

/*!
 * @brief function of getting tail
 * @return queue tail
 */

int Queue::get_tail() const
{
    return tail;
}

/*!
 * @brief function of getting size of queue
 * @return queue size
 */

int Queue::get_size() const
{
    return size;
}

/*!
 * @brief function of getting max size of queue array
 * @return max size
 */

int Queue::get_max_size() const
{
    return max_size;
}

/*!
 * @brief function of getting queue array with Messages
 * @return chats
 */

const Message *Queue::get_chats() const
{
    return chats;
}

/*!
 * @brief function which set new head of queue
 * @param new_head new head of queue
 */

void Queue::set_head(int new_head)
{
    head = new_head;
}

/*!
 * @brief function which set new tail of queue
 * @param new_tail new tail of queue
 */

void Queue::set_tail(int new_tail)
{
    tail = new_tail;
}

/*!
 * @brief function which set new size of queue
 * @param new_size new size of queue
 */

void Queue::set_size(int new_size)
{
    size = new_size;
}

/*!
 * @brief function which set new max size of queue
 * @param new_size new max size of queue
 */

void Queue::set_max_size(int new_size)
{
    max_size = new_size;
}

/*!
 * @brief function which set new chats-array
 * @param new_chats new array
 * @param count number of elements in new array
 */

void Queue::set_chats(const Message *new_chats, int count)
{
    if (count > max_size)
    {
        max_size = count;
        resize(count);
    }
    Message *temp = nullptr;
    try
    {
        temp = new Message[max_size];
        std::copy(new_chats, new_chats + count, temp);
        delete[] chats;
        chats = temp;
        head = 0;
        tail = count;
        size = count;
    }
    catch (const std::exception &e)
    {
        delete[] temp;
        throw;
    }
}

/*!
 * @brief the copying constructor
 */

Queue::Queue(const Queue &queue) : max_size(queue.max_size), size(queue.size), head(queue.head), tail(queue.tail)
{
    try
    {
        chats = new Message[queue.max_size];
        for (int i = 0; i < max_size; ++i)
        {
            chats[i] = queue.chats[(queue.head + i) % queue.max_size];
        }
    }
    catch (const std::exception &e)
    {
        delete[] chats;
        throw;
    }
}

/*!
 * @brief the moving constructor
 */

Queue::Queue(Queue &&queue) noexcept
    : max_size(queue.max_size), size(queue.size), head(queue.head), tail(queue.tail), chats(queue.chats)
{
    queue.size = 0;
    queue.head = 0;
    queue.tail = 0;
    queue.chats = nullptr;
}

/*!
 * @brief the moving operator
 *
 * @param queue
 * @return changed queue
 */

Queue &Queue::operator=(Queue &&queue) noexcept
{
    if (this != &queue)
    {
        delete[] chats;
        head = queue.head;
        tail = queue.tail;
        size = queue.size;
        max_size = queue.max_size;
        chats = queue.chats;
        queue.head = 0;
        queue.tail = 0;
        queue.max_size = 0;
        queue.size = 0;
        queue.chats = nullptr;
    }
    return *this;
}

/*!
 * @brief add new Message
 *
 * @param rsh the second operand
 * @return changed queue
 */

Queue &Queue::operator+=(const Message &rsh)
{
    if (this->check_queue() == FULL)
    {
        resize(this->get_size() * 2);
    }
    chats[this->get_tail()] = rsh;
    int new_tail = (this->get_tail() + 1) % this->get_max_size();
    this->set_tail(new_tail);
    int size = this->get_size();
    this->set_size(size + 1);
    return *this;
}

/*!
 * @brief Reading message
 *
 * @throws std::logic_error() if the queue is empty
 * @return Read message
 */

Message Queue::pop()
{
    if (this->check_queue() == EMPTY)
    {
        throw std::logic_error("Stack is empty");
    }
    Message message = this->get_chats()[this->get_head()];
    int head = (this->get_head() + 1) % this->get_max_size();
    this->set_head(head);
    int size = this->get_size();
    this->set_size(size - 1);
    return message;
}

/*!
 * @brief Check the state of queue
 *
 * @return EMPTY if the queue is empty
 * @return FULL if the queue is full
 * @return HALF_FULL if the queue is half-full
 */

int Queue::check_queue()
{
    if (this->get_size() == 0)
    {
        return EMPTY;
    }
    else if (this->get_size() == this->get_max_size())
    {
        return FULL;
    }
    return HALF_FULL;
}

/*!
 * @brief combining messages from the same chat
 *
 * @throws std::logic_error() if the queue is empty
 * @return new queue
 */

Queue Queue::reorganization()
{
    if (this->check_queue() == EMPTY)
    {
        throw std::logic_error("Stack is empty");
    }
    auto view = this->get_queue_range();
    Queue arr;
    std::vector<Message> result;
    Message *q_chats = new Message[this->get_size()];
    try
    {
        std::for_each(view.begin(), view.end(), [&result](const Message &val)
                      {
            if (!result.empty() && result.back().get_chat() == val.get_chat()){
                Message new_message = result.back().add(val);
                result.back() = new_message;
            }
            else{
                result.push_back(val);
            } });
        std::copy(result.begin(), result.end(), q_chats);
        arr.set_chats(q_chats, result.size());
        arr.set_tail(result.size());
    }
    catch (const std::exception &e)
    {
        delete[] q_chats;
        throw;
    }
    delete[] q_chats;
    return arr;
}

/*!
 * @brief find message by word
 * @param word the word which message is being searched for
 * @throws std::runtime_error() if the message isn`t found
 * @return found message
 */
const Message Queue::find_message(const std::string &word)
{
    auto view = this->get_queue_range();
    auto iter = std::find_if(view.begin(), view.end(),
                             [&word](const Message &val)
                             {
                                 return val.find_word(word);
                             });

    if (iter == view.end())
    {
        throw std::runtime_error("Message not found");
    }
    return *iter;
}

/*!
 * @brief combine messages from the same chat into new queue
 * @param chat_name the name of chat
 * @return new queue
 */
Queue Queue::operator[](const std::string &chat_name)
{
    Queue new_queue;
    std::vector<Message> elements;
    auto view = this->get_queue_range();
    auto iter = std::copy_if(view.begin(), view.end(), std::back_inserter(elements), [&chat_name](const Message &val)
                             { return val.get_chat() == chat_name; });
    Message *res = new Message[this->get_max_size()];
    try
    {
        std::copy(elements.begin(), elements.end(), res);
        auto tail = elements.end() - elements.begin();
        new_queue.set_chats(res, tail);
        new_queue.set_tail(tail);
    }
    catch (const std::exception &e)
    {
        delete[] res;
        throw;
    }
    delete[] res;
    return new_queue;
}

/*!
 * @brief queue arranging
 * @throws std::out_of_range() if queue empty
 */

void Queue::arrange()
{
    if (this->check_queue() == EMPTY)
    {
        throw std::out_of_range("Empty queue");
    }
    Message *chats = new Message[this->get_size()];
    try
    {
        auto view = this->get_queue_range();
        std::copy(view.begin(), view.end(), chats);
        std::sort(chats, chats + this->get_size());
        this->set_chats(chats, this->get_size());
    }
    catch (const std::exception &e)
    {
        delete[] chats;
        throw;
    }
    delete[] chats;
}

/*!
 * @brief create new queue from vector of Messages
 * @param messages vector
 * @param count lentgth of vector
 */

void Queue::from_vec(const Message *messages, int count)
{
    if (count > this->get_max_size())
    {
        this->resize(this->get_max_size() * 2);
    }
    this->set_chats(messages, count);
    this->set_tail(count);
    this->set_size(count);
}

/*!
 * @brief Input queue class operator
 * @param in input stream
 * @param queue the queue in which the data is written
 * @return input steam
 */

std::istream &operator>>(std::istream &in, Queue &queue)
{
    Queue new_queue;
    int count;
    try
    {
        in >> count;
        if (check_input(in) == false)
            return in;
        Message msg;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < count; ++i)
        {
            in >> msg;
            if (!in.good())
                return in;
            new_queue += msg;
        }
        queue = std::move(new_queue);
    }
    catch (const std::runtime_error &e)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

/*!
 * @brief Output queue class operator
 * @param out output stream
 * @param queue the queue from which the data is written
 * @return output steam
 */

std::ostream &operator<<(std::ostream &out, Queue &queue)
{
    auto view = queue.get_queue_range();
    std::for_each(view.begin(), view.end(), [&out](const Message &msg)
                  { out << msg; });
    out << "\n";
    return out;
}

/*!
 * @brief Copying an instance of a complex class
 * @param queue the queue from which the data is written
 * @return modified queue
 */

Queue &Queue::operator=(const Queue &queue)
{
    Message *new_chats = new Message[queue.get_max_size()];
    try
    {
        for (int i = 0; i < queue.get_size(); ++i)
        {
            new_chats[i] = queue.get_chats()[(queue.get_head() + i) % queue.get_max_size()];
        }
        this->set_chats(new_chats, queue.get_size());
        this->set_head(queue.get_head());
        this->set_tail(queue.get_tail());
        this->set_size(queue.get_size());
        this->set_max_size(queue.get_max_size());
        delete[] new_chats;
    }
    catch (const std::exception &e)
    {
        delete[] new_chats;
        throw;
    }
    return *this;
}
