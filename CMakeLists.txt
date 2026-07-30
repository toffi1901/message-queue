cmake_minimum_required(VERSION 3.10)
project(MyProgect VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0  
)

FetchContent_MakeAvailable(googletest)

message(STATUS "FetchContent_MakeAvailable(googletest) completed")
message(STATUS "googletest source dir: ${googletest_SOURCE_DIR}")
message(STATUS "googletest binary dir: ${googletest_BINARY_DIR}")

add_library(messages message.cpp check.cpp time.cpp queue.cpp in_out_put.cpp)

add_executable(lab2 main.cpp)

target_link_libraries(lab2 messages)


enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0  
)

FetchContent_MakeAvailable(googletest)

message(STATUS "FetchContent_MakeAvailable(googletest) completed")
message(STATUS "googletest source dir: ${googletest_SOURCE_DIR}")
message(STATUS "googletest binary dir: ${googletest_BINARY_DIR}")

add_executable(tests tests.cpp message.cpp check.cpp time.cpp queue.cpp in_out_put.cpp)
target_include_directories(tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include ${googletest_SOURCE_DIR}/googlemock/include)
target_link_libraries(tests gtest gmock pthread)

target_compile_options(tests PRIVATE --coverage)
target_link_options(tests PRIVATE --coverage)

add_test(NAME QueueTest_SetHead COMMAND tests --gtest_filter=QueueTest.SetHead)
add_test(NAME QueueTest_SetTail COMMAND tests --gtest_filter=QueueTest.SetTail)
add_test(NAME QueueTest_SetMaxSize COMMAND tests --gtest_filter=QueueTest.SetMaxSize)
add_test(NAME QueueTest_SetSize COMMAND tests --gtest_filter=QueueTest.SetSize)
add_test(NAME QueueTest_SetChatsTest COMMAND tests --gtest_filter=QueueTest.SetChatsTest)
add_test(NAME QueueTest_GetSize COMMAND tests --gtest_filter=QueueTest.GetSize)
add_test(NAME QueueTest_GetHead COMMAND tests --gtest_filter=QueueTest.GetHead)
add_test(NAME QueueTest_GetTail COMMAND tests --gtest_filter=QueueTest.GetTail)
add_test(NAME QueueTest_GetMaxSize COMMAND tests --gtest_filter=QueueTest.GetMaxSize)

add_test(NAME QueueTest_DefaultConstructor COMMAND tests --gtest_filter=QueueTest.DefaultConstructor)
add_test(NAME QueueTest_CopyConstructor COMMAND tests --gtest_filter=QueueTest.CopyConstructor)
add_test(NAME QueueTest_MoveConstructor COMMAND tests --gtest_filter=QueueTest.MoveConstructor)

add_test(NAME QueueTest_AssignOperator COMMAND tests --gtest_filter=QueueTest.AssignOperator)
add_test(NAME QueueTest_AddMessage COMMAND tests --gtest_filter=QueueTest.AddMessage)
add_test(NAME QueueTest_MoveOperator COMMAND tests --gtest_filter=QueueTest.MoveOperator)
add_test(NAME QueueTest_PopMessageValid COMMAND tests --gtest_filter=QueueTest.PopMessageValid)
add_test(NAME QueueTest_PopMessageInvalid COMMAND tests --gtest_filter=QueueTest.PopMessageInvalid)
add_test(NAME QueueTest_CheckStateEmpty COMMAND tests --gtest_filter=QueueTest.CheckStateEmpty)
add_test(NAME QueueTest_CheckStateHalf COMMAND tests --gtest_filter=QueueTest.CheckStateHalf)

add_test(NAME QueueTest_InvalidReorganization COMMAND tests --gtest_filter=QueueTest.InvalidReorganization)
add_test(NAME QueueTest_FindMessageTest COMMAND tests --gtest_filter=QueueTest.FindMessageTest)
add_test(NAME QueueTest_InvalidFindMessageTest COMMAND tests --gtest_filter=QueueTest.InvalidFindMessageTest)
add_test(NAME QueueTest_CommonChatsTest COMMAND tests --gtest_filter=QueueTest.CommonChatsTest)
add_test(NAME QueueTest_ReorganizationQueue COMMAND tests --gtest_filter=QueueTest.ReorganizationQueue)
add_test(NAME QueueTest_ArrangeQueueTest COMMAND tests --gtest_filter=QueueTest.ArrangeQueueTest)
add_test(NAME QueueTest_ClassFromVector COMMAND tests --gtest_filter=QueueTest.ClassFromVector)
add_test(NAME QueueTest_CopyOperator COMMAND tests --gtest_filter=QueueTest.CopyOperator)
add_test(NAME QueueTest_QueueInputOperator COMMAND tests --gtest_filter=QueueTest.QueueInputOperator)

add_test(NAME QueueTest_InputOperator COMMAND tests --gtest_filter=QueueTest.InputOperator)
add_test(NAME QueueTest_OutputOperatorr COMMAND tests --gtest_filter=QueueTest.OutputOperator)

add_test(NAME MessageTest_DefaultConstructor COMMAND tests --gtest_filter=MessageTest.DefaultConstructor)
add_test(NAME MessageTest_InitConstructorWithTime COMMAND tests --gtest_filter=MessageTest.InitConstructorWithTime)
add_test(NAME MessageTest_InitConstructor COMMAND tests --gtest_filter=MessageTest.InitConstructor)

add_test(NAME MessageTest_Add COMMAND tests --gtest_filter=MessageTest.Add)
add_test(NAME MessageTest_AddInvalid COMMAND tests --gtest_filter=MessageTest.AddInvalid)
add_test(NAME MessageTest_FindWord COMMAND tests --gtest_filter=MessageTest.FindWord)
add_test(NAME MessageTest_NoFindWord COMMAND tests --gtest_filter=MessageTest.NoFindWord)
add_test(NAME MessageTest_Equalness COMMAND tests --gtest_filter=MessageTest.Equalness)
add_test(NAME MessageTest_LessTest COMMAND tests --gtest_filter=MessageTest.LessTest)
add_test(NAME MessageTest_GreaterTest COMMAND tests --gtest_filter=MessageTest.GreaterTest)

add_test(NAME MessageTest_InputOperator COMMAND tests --gtest_filter=MessageTest.InputOperator)
add_test(NAME MessageTest_OutputOperator COMMAND tests --gtest_filter=MessageTest.OutputOperator)

add_test(NAME splitTest_ValidInput COMMAND tests --gtest_filter=splitTest.ValidInput)
add_test(NAME ParseTimeTest_ValidInput COMMAND tests --gtest_filter=ParseTimeTest.ValidInput)
add_test(NAME ParseTimeTest_InvalidInput COMMAND tests --gtest_filter=ParseTimeTest.InvalidInput)
add_test(NAME ParseTimeTest_InvalidFormat COMMAND tests --gtest_filter=ParseTimeTest.InvalidFormat)
add_test(NAME ParseTimeTest_EmptyInput COMMAND tests --gtest_filter=ParseTimeTest.EmptyInput)
add_test(NAME CheckInputTest_BadInput COMMAND tests --gtest_filter=CheckInputTest.BadInput)
add_test(NAME CheckInputTest_EOFInput COMMAND tests --gtest_filter=CheckInputTest.EOFInput)


add_test(NAME GetIntTest_OutOfRangeInputThenValid COMMAND tests --gtest_filter=GetIntTest.OutOfRangeInputThenValid)
add_test(NAME GetIntTest_EOFInput COMMAND tests --gtest_filter=GetIntTest.EOFInput)

add_test(NAME InputTimeTest_InvalidInput COMMAND tests --gtest_filter=InputTimeTest.InvalidInput)
add_test(NAME InputTimeTest_BadInput COMMAND tests --gtest_filter=InputTimeTest.BadInput)
add_test(NAME QueueTest_ResizeSuccess COMMAND tests --gtest_filter=QueueTest.ResizeSuccess)
add_test(NAME QueueTest_NotFull COMMAND tests --gtest_filter=QueueTest.NotFull)


add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS tests
)

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E remove_directory coverage_report
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage_report
    COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH}" gcovr --root ${CMAKE_SOURCE_DIR} --html --html-details -o coverage_report/index.html --exclude='_deps/googletest-src/.*' --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS run_tests
    COMMENT "Generating code coverage report with gcovr"
)