cmake_minimum_required(VERSION 3.11)
project(test_rbtree LANGUAGES CXX)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

macro(add_gtest TESTNAME)
    # create an executable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})

    # link gtest
    target_link_libraries(${TESTNAME} gtest gtest_main)

    target_include_directories(${TESTNAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../src
                           ${CMAKE_CURRENT_SOURCE_DIR}/../MyRedBlackTree/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/test_implementation)

    add_test(${TESTNAME} ${TESTNAME})
endmacro()

add_gtest(test_rbtree test_rbtree.cc)
