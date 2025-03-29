cmake_minimum_required(VERSION 3.11)
project(MyRedBlackTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rbt_main src/rbt_main.cc)
target_include_directories(rbt_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
