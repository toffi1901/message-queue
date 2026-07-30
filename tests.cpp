#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdlib>
#include "queue.h"

bool operator==(const Message &lhs, const Message &rhs)
{
    return lhs.get_message() == rhs.get_message() &&
           lhs.get_chat() == rhs.get_chat() &&
           lhs.get_timeline() == rhs.get_timeline();
}

TEST(QueueTest, SetHead)
{
    Queue queue;
    queue.set_head(2);
    EXPECT_EQ(queue.get_head(), 2);
}

TEST(QueueTest, SetTail)
{
    Queue queue;
    queue.set_tail(2);
    EXPECT_EQ(queue.get_tail(), 2);
}

TEST(QueueTest, SetSize)
{
    Queue queue;
    queue.set_size(2);
    EXPECT_EQ(queue.get_size(), 2);
}

TEST(QueueTest, SetMaxSize)
{
    Queue queue;
    queue.set_max_size(2);
    EXPECT_EQ(queue.get_max_size(), 2);
}

TEST(QueueTest, SetChatsTest)
{
    Queue queue;
    int count = 2;
    Message new_chats[count] = {
        {"msg1", "chat1"},
        {"msg2", "chat2"},
    };
    queue.set_chats(new_chats, count);
    EXPECT_EQ(queue.get_size(), count);
    EXPECT_EQ(queue.get_max_size(), 10);
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_tail(), count);
    for (int i = 0; i < count; ++i)
    {
        EXPECT_EQ(queue.get_chats()[i].get_message(), new_chats[i].get_message());
        EXPECT_EQ(queue.get_chats()[i].get_chat(), new_chats[i].get_chat());
    }
}

TEST(QueueTest, GetSize)
{
    Queue queue;
    queue.set_size(20);
    EXPECT_EQ(queue.get_size(), 20);
}

TEST(QueueTest, GetHead)
{
    Queue queue;
    EXPECT_EQ(queue.get_head(), 0);
}

TEST(QueueTest, GetTail)
{
    Queue queue;
    EXPECT_EQ(queue.get_tail(), 0);
}

TEST(QueueTest, GetMaxSize)
{
    Queue queue;
    EXPECT_EQ(queue.get_max_size(), 10);
}

TEST(QueueTest, GetChats)
{
    Queue queue;
    EXPECT_EQ(queue.get_size(), 0);
    EXPECT_EQ(queue.get_max_size(), 10);
}

TEST(QueueTest, DefaultConstructor)
{
    Queue queue;
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_tail(), 0);
    EXPECT_EQ(queue.get_size(), 0);
    EXPECT_EQ(queue.get_max_size(), 10);
    EXPECT_NE(queue.get_chats(), nullptr);
}

TEST(QueueTest, CopyConstructor)
{
    Queue queue;
    Message msg("message1", "chat");
    queue += msg;
    Queue new_queue(queue);
    EXPECT_EQ(queue.get_head(), new_queue.get_head());
    EXPECT_EQ(queue.get_tail(), new_queue.get_tail());
    EXPECT_EQ(queue.get_size(), new_queue.get_size());
    EXPECT_EQ(queue.get_max_size(), new_queue.get_max_size());
    EXPECT_EQ(queue.get_chats()[queue.get_tail() - 1], new_queue.get_chats()[new_queue.get_tail() - 1]);
}

TEST(QueueTest, MoveConstructor)
{
    Queue queue;
    Message msg("message1", "chat");
    queue += msg;
    Queue new_queue(std::move(queue));
    EXPECT_EQ(new_queue.get_head(), 0);
    EXPECT_EQ(new_queue.get_size(), 1);
    EXPECT_EQ(new_queue.get_tail(), 1);
    EXPECT_EQ(queue.get_chats(), nullptr);
}

TEST(QueueTest, AssignOperator)
{
    Queue queue;
    Queue new_queue;
    Message msg("message1", "chat");
    queue += msg;
    new_queue = queue;
    EXPECT_EQ(new_queue.get_size(), 1);
    EXPECT_EQ(new_queue.get_tail(), 1);
    EXPECT_EQ(new_queue.get_chats()[new_queue.get_tail() - 1], msg);
}

TEST(QueueTest, AddMessage)
{
    Queue queue;
    Message msg("message", "chat");
    queue += msg;
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_tail(), 1);
    EXPECT_EQ(queue.get_chats()[0], msg);
}

TEST(QueueTest, MoveOperator)
{
    Queue queue;
    Queue new_queue;
    Message msg("message1", "chat");
    queue += msg;
    new_queue = std::move(queue);
    EXPECT_EQ(new_queue.get_head(), 0);
    EXPECT_EQ(new_queue.get_tail(), 1);
    EXPECT_EQ(new_queue.get_size(), 1);
    EXPECT_EQ(queue.get_chats(), nullptr);
}

TEST(QueueTest, PopMessageValid)
{
    Queue queue;
    Message msg;
    msg.set_message("message1");
    msg.set_chat("chat");
    queue += msg;
    Message res = queue.pop();
    EXPECT_EQ(queue.get_head(), 1);
    EXPECT_EQ(queue.get_tail(), 1);
    EXPECT_EQ(queue.get_size(), 0);
    EXPECT_EQ(res.get_message(), msg.get_message());
    EXPECT_EQ(res.get_chat(), msg.get_chat());
}

TEST(QueueTest, PopMessageInvalid)
{
    Queue queue;
    EXPECT_THROW(queue.pop(), std::logic_error);
}

TEST(QueueTest, CheckStateEmpty)
{
    Queue queue;
    EXPECT_EQ(queue.check_queue(), EMPTY);
}

TEST(QueueTest, CheckStateHalf)
{
    Queue queue;
    Message msg;
    msg.set_message("message1");
    msg.set_chat("chat");
    queue += msg;
    EXPECT_EQ(queue.check_queue(), HALF_FULL);
}

TEST(QueueTest, ArrangeQueueTest)
{
    Queue queue;
    Message msg1("message1", "chat2");
    Message msg2("message2", "chat1");
    queue += msg1;
    queue += msg2;
    queue.arrange();
    EXPECT_EQ(queue.get_tail(), 2);
    EXPECT_EQ(queue.get_size(), 2);
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_chats()[0], msg2);
    EXPECT_EQ(queue.get_chats()[1], msg1);
}

TEST(QueueTest, CommonChatsTest)
{
    Queue queue;
    Queue new_queue;
    Message msg1("message1", "chat");
    Message msg2("message2", "chat");
    Message msg3("message2", "chat1");
    queue += msg1;
    queue += msg2;
    queue += msg3;
    new_queue = queue["chat"];
    EXPECT_EQ(new_queue.get_tail(), 2);
    EXPECT_EQ(new_queue.get_size(), 2);
    EXPECT_EQ(new_queue.get_head(), 0);
    EXPECT_EQ(new_queue.get_chats()[0], msg1);
    EXPECT_EQ(new_queue.get_chats()[1], msg2);
}

TEST(QueueTest, ReorganizationQueue)
{
    Queue queue;
    Message msg1("message1", "chat");
    Message msg2("message2", "chat");
    queue += msg1;
    queue += msg2;
    Queue new_queue = queue.reorganization();
    queue = new_queue;
    Message msg = msg1.add(msg2);
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_tail(), 1);
    EXPECT_EQ(queue.get_size(), 1);
    EXPECT_EQ(queue.get_chats()[0], msg);
}

TEST(QueueTest, InvalidReorganization)
{
    Queue queue;
    EXPECT_THROW(queue.reorganization(), std::logic_error);
}

TEST(QueueTest, FindMessageTest)
{
    Queue queue;
    Message msg1("message1", "chat");
    Message msg2("message2", "chat");
    queue += msg1;
    queue += msg2;
    Message msg = queue.find_message("message2");
    EXPECT_EQ(msg, msg2);
}

TEST(QueueTest, InvalidFindMessageTest)
{
    Queue queue;
    EXPECT_THROW(queue.find_message("message3"), std::runtime_error);
}

TEST(QueueTest, ClassFromVector)
{
    Message messages[2] = {Message("message1", "chat"), Message("message2", "chat")};
    Queue queue;
    queue.from_vec(messages, 2);

    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_tail(), 2);
    EXPECT_EQ(queue.get_size(), 2);
    EXPECT_EQ(queue.get_chats()[0], messages[0]);
    EXPECT_EQ(queue.get_chats()[1], messages[1]);
}

TEST(QueueTest, CopyOperator)
{
    Queue queue, new_queue;
    Message msg("message1", "chat2");
    queue += msg;
    new_queue = queue;
    EXPECT_EQ(new_queue.get_tail(), 1);
    EXPECT_EQ(new_queue.get_size(), 1);
    EXPECT_EQ(new_queue.get_head(), 0);
    EXPECT_EQ(new_queue.get_chats()[0], msg);
}

TEST(QueueTest, QueueInputOperator)
{
    Queue queue, new_queue;
    Message msg("message1", "chat2");
    queue += msg;
    new_queue = queue;
    EXPECT_EQ(new_queue.get_tail(), 1);
    EXPECT_EQ(new_queue.get_size(), 1);
    EXPECT_EQ(new_queue.get_head(), 0);
    EXPECT_EQ(new_queue.get_chats()[0], msg);
}

TEST(QueueTest, InputOperator)
{
    std::stringstream input("1\nmsg\nchat\n21.02.2002 12:12\n");
    Queue queue;
    input >> queue;
    std::string str_time = "21.02.2002 12:12";
    time_point<system_clock> time;
    parse_time(str_time, time);
    Message msg("msg", "chat", time);
    EXPECT_EQ(queue.get_size(), 1);
    EXPECT_EQ(queue.get_tail(), 1);
    EXPECT_EQ(queue.get_head(), 0);
    EXPECT_EQ(queue.get_chats()[0], msg);
}

TEST(QueueTest, OutputOperator)
{
    Queue queue;
    Message msg;
    std::string time = "21.02.2000 12:00";
    std::chrono::system_clock::time_point time_msg;
    parse_time(time, time_msg);
    msg.set_message("msg");
    msg.set_chat("chat");
    msg.set_time(time_msg);
    queue += msg;
    std::stringstream output;
    output << queue;
    EXPECT_EQ(output.str(), "msg chat 21.02.2000 09:00\n\n");
}

TEST(MessageTest, DefaultConstructor)
{
    Message msg;
    EXPECT_EQ(msg.get_message(), "");
    EXPECT_EQ(msg.get_chat(), "");
}

TEST(MessageTest, InitConstructorWithTime)
{
    std::string pre_message = "msg";
    std::string chat_name = "chat";
    std::string str_time = "20.02.2000 12:00";
    time_point<system_clock> time;
    parse_time(str_time, time);
    Message msg(pre_message, chat_name, time);
    EXPECT_EQ(msg.get_message(), pre_message);
    EXPECT_EQ(msg.get_chat(), chat_name);
    EXPECT_EQ(msg.get_timeline(), time);
}

TEST(MessageTest, InitConstructor)
{
    std::string pre_message = "msg";
    std::string chat_name = "chat";
    time_point<system_clock> time = system_clock::now();
    Message msg(pre_message, chat_name);
    EXPECT_EQ(msg.get_message(), pre_message);
    EXPECT_EQ(msg.get_chat(), chat_name);
    auto msg_time = msg.get_timeline();
    auto time_diff = duration_cast<milliseconds>(time - msg_time).count();
    EXPECT_LE(time_diff, 100);
}

TEST(MessageTest, Add)
{
    Message msg1("message1", "chat");
    Message msg2("message2", "chat");
    Message msg = msg1.add(msg2);
    EXPECT_EQ(msg.get_message(), "message1message2");
    EXPECT_EQ(msg.get_chat(), "chat");
}

TEST(MessageTest, AddInvalid)
{
    Message msg1, msg2;
    msg1.set_message("message1");
    msg1.set_chat("chat1");
    msg2.set_message("message2");
    msg2.set_chat("chat2");
    EXPECT_THROW(msg1.add(msg2), std::runtime_error);
}

TEST(MessageTest, FindWord)
{
    Message msg;
    std::string word = "word";
    msg.set_message("word");
    msg.set_chat("chat1");
    bool val = msg.find_word(word);
    EXPECT_EQ(val, true);
}

TEST(MessageTest, NoFindWord)
{
    Message msg;
    std::string word = "word";
    msg.set_message("w");
    msg.set_chat("chat1");
    bool val = msg.find_word(word);
    EXPECT_EQ(val, false);
}

TEST(MessageTest, Equalness)
{
    Message msg1, msg2;
    msg1.set_message("message1");
    msg1.set_chat("chat");
    msg2.set_message("message2");
    msg2.set_chat("chat");
    EXPECT_EQ(msg1 <=> msg2, std::weak_ordering::equivalent);
}

TEST(MessageTest, LessTest)
{
    Message msg1, msg2;
    msg1.set_message("message1");
    msg1.set_chat("chat1");
    msg2.set_message("message2");
    msg2.set_chat("chat2");
    EXPECT_EQ(msg1 <=> msg2, std::weak_ordering::less);
}

TEST(MessageTest, GreaterTest)
{
    Message msg1, msg2;
    msg1.set_message("message1");
    msg1.set_chat("chat2");
    msg2.set_message("message2");
    msg2.set_chat("chat1");
    EXPECT_EQ(msg1 <=> msg2, std::weak_ordering::greater);
}

TEST(MessageTest, InputOperator)
{
    std::stringstream input("msg\nchat\n12.02.2001 12:20\n");
    Message msg;
    input >> msg;
    time_point<system_clock> time;
    parse_time("12.02.2001 12:20", time);
    msg.set_message("msg");
    msg.set_chat("chat");
    msg.set_time(time);
    EXPECT_EQ(msg.get_message(), "msg");
    EXPECT_EQ(msg.get_chat(), "chat");
    EXPECT_EQ(msg.get_timeline(), time);
}

TEST(MessageTest, OutputOperator)
{
    Message msg;
    std::chrono::system_clock::time_point time;
    parse_time("12.02.2001 12:20", time);
    msg.set_message("msg");
    msg.set_chat("chat");
    msg.set_time(time);
    std::stringstream output;
    output << msg;
    EXPECT_EQ(output.str(), "msg chat 12.02.2001 09:20\n");
}

TEST(splitTest, ValidInput)
{
    std::vector<std::string> tokens;
    std::string inputt = "{\"key\" : \"value\"}";
    tokens = split(inputt, "{}: ");
    EXPECT_THAT(tokens, testing::ElementsAre("\"key\"", "\"value\""));
}

TEST(ParseTimeTest, ValidInput)
{
    std::chrono::system_clock::time_point time;
    EXPECT_TRUE(parse_time("21.02.2001 12:30", time));
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&tt);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y %H:%M");
    EXPECT_EQ(oss.str(), "21.02.2001 12:30");
}

TEST(ParseTimeTest, InvalidInput)
{
    std::chrono::system_clock::time_point time;
    EXPECT_FALSE(parse_time("invalid_date_time", time));
}

TEST(ParseTimeTest, InvalidFormat)
{
    std::chrono::system_clock::time_point time;
    EXPECT_FALSE(parse_time("01/01/2023 12:30", time));
}

TEST(ParseTimeTest, EmptyInput)
{
    std::chrono::system_clock::time_point time;
    EXPECT_FALSE(parse_time("", time));
}

TEST(CheckInputTest, BadInput)
{
    std::string input = "Bad input";
    std::stringstream in(input);
    in.setstate(std::ios::badbit);
    std::cin.rdbuf(in.rdbuf());
    std::string result;
    EXPECT_THROW(check_input(result), std::runtime_error);
}

TEST(CheckInputTest, EOFInput)
{
    std::string input = "EOF input";
    std::stringstream in(input);
    in.setstate(std::ios::eofbit);
    std::cin.rdbuf(in.rdbuf());

    std::string result;
    EXPECT_THROW(check_input(result), std::runtime_error);
}

TEST(GetIntTest, OutOfRangeInputThenValid)
{
    std::istringstream input("15 5");
    int option;
    EXPECT_TRUE(getint(input, option, 1, 10));
    EXPECT_EQ(option, 5);
}

TEST(GetIntTest, EOFInput)
{
    std::istringstream input("");
    int option;
    EXPECT_THROW(getint(input, option, 1, 10), std::runtime_error);
}

TEST(InputTimeTest, InvalidInput)
{
    std::istringstream input("invalid_format");
    EXPECT_THROW(input_time(input), std::runtime_error);
}

TEST(InputTimeTest, BadInput)
{
    std::istringstream input("bad_input");
    EXPECT_THROW(input_time(input), std::runtime_error);
}

TEST(QueueTest, ResizeSuccess)
{
    Queue queue;
    Message msg("message1", "chat");
    Message msg1("message2", "chat");
    Message msg2("message3", "chat");
    Message msg3("message1", "chat");
    Message msg4("message2", "chat");
    Message msg5("message3", "chat");
    Message msg6("message1", "chat");
    Message msg7("message2", "chat");
    Message msg8("message3", "chat");
    Message msg9("message1", "chat");
    queue+=msg;
    queue+=msg1;
    queue+=msg2;
    queue+=msg3;
    queue+=msg4;
    queue+=msg5;
    queue+=msg6;
    queue+=msg7;
    queue+=msg8;
    queue+=msg9;
    queue.test_resize(20);
    EXPECT_EQ(queue.get_max_size(), 20);
    EXPECT_EQ(queue.get_size(), 10);
}
TEST(QueueTest, NotFull)
{
    Queue queue;
    EXPECT_THROW(queue.test_resize(20), std::runtime_error);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}