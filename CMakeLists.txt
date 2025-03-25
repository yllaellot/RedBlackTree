cmake_minimum_required(VERSION 3.11)
project(set LANGUAGES CXX)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GTest
add_subdirectory("./googletest")
mark_as_advanced(BUILD_GTEST BUILD_SHARED_LIBS)
enable_testing()

include_directories(./MyRedBalackTree MyRedBalackTree)

add_subdirectory(./set set)
add_subdirectory(./tests)