
#include <iostream>
#include "queue.h"
#include "message.h"

int dio(Queue &queue)
{
    int option = -1;
    try
    {
        do
        {
            Queue new_queue;
            Queue temp;
            std::string message;
            std::string word;
            Message m;
            Message msg;
            int state;
            std::cout << "0 - exit" << std::endl;
            std::cout << "1 - input queue" << std::endl;
            std::cout << "2 - output queue" << std::endl;
            std::cout << "3 - add new message" << std::endl;
            std::cout << "4 - pop message" << std::endl;
            std::cout << "5 - check the state of queue" << std::endl;
            std::cout << "6 - reorganization of queue" << std::endl;
            std::cout << "7 - new queue with equal chats" << std::endl;
            std::cout << "8 - find message by the word" << std::endl;
            std::cout << "9 - sort queue" << std::endl;
            std::cout << "Choose option" << std::endl;

            getint(std::cin, option, 0, 9);
            switch (option)
            {
            case 0:
                std::cout << "Exiting..." << std::endl;
                return 0;
            case 1:
                queue.input_queue();
                break;

            case 2:
                std::cout << queue;
                break;
            case 3:
                msg.input_message();
                queue += msg;
                break;
            case 4:
                msg = queue.pop();
                msg.output_message();
                // std::cout << msg;
                break;
            case 5:
                state = queue.check_queue();
                if (state == FULL)
                    std::cout << "Queue is full" << std::endl;
                else if (state == HALF_FULL)
                    std::cout << "Queue half-full" << std::endl;
                else
                    std::cout << "Queue is empty" << std::endl;
                break;
            case 6:
                new_queue = queue.reorganization();
                queue = new_queue;
                break;
            case 7:
                std::cout << "Input chat name: " << std::endl;
                // check_input(word);
                std::cin >> word;
                new_queue = queue[word];
                if (new_queue.check_queue() != EMPTY)
                {
                    std::cout << "New queue: " << new_queue << std::endl;
                }
                else
                {
                    std::cout << "No chats" << std::endl;
                }
                break;
            case 8:
                std::cout << "Input word: " << std::endl;
                std::cin >> word;
                temp = queue;
                m = temp.find_message(word);
                std::cout << "The message is: " << m << std::endl;
                break;
            case 9:
                queue.arrange();
                break;
            }
        } while (option != 0);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int main()
{
    try
    {
        Queue queue;
        dio(queue);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
