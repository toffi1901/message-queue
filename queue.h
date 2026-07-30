#ifndef QUEUE_H
#define QUEUE_H

#include "message.h"

#include <ranges>
#include <algorithm>

enum QueueState
{
    FULL = 2,
    HALF_FULL = 1,
    EMPTY = 0,
};

class Queue
{
private:
    size_t max_size;
    size_t size;
    size_t head;
    size_t tail;
    Message *chats;
    void resize(int size);
    auto get_queue_range();

public:
    Queue() : head(0), tail(0), max_size(10), size(0), chats(new Message[max_size]) {};

    Queue(const Queue &);
    Queue(Queue &&queue) noexcept;
    Queue &operator=(Queue &&queue) noexcept;
    ~Queue() { delete[] chats; }

    Queue &operator+=(const Message &rsh);
    Queue operator[](const std::string &chat);
    Queue &operator=(const Queue &queue);
    friend std::ostream &operator<<(std::ostream &out, Queue &queue);
    friend std::istream &operator>>(std::istream &in, Queue &queue);

    Message pop();

    int get_head() const;
    int get_tail() const;
    int get_size() const;
    int get_max_size() const;
    const Message *get_chats() const;

    void set_head(int new_head);
    void set_tail(int new_tail);
    void set_size(int new_size);
    void set_max_size(int new_size);
    void set_chats(const Message *new_chats, int count);

    int check_queue();
    Queue reorganization();
    void from_vec(const Message *messages, int count);
    void arrange();
    void input_queue();
    void output_queue();
    void copy_vector(const Queue &queue);
    const Message find_message(const std::string &word);
    void test_resize(int new_size) { resize(new_size); }
};

#endif