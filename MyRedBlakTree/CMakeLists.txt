cmake_minimum_required(VERSION 3.11)
project(MyRedBlackTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rb_tree src/rb_tree.cc)
target_include_directories(rb_tree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
