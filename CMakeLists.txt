cmake_minimum_required(VERSION 3.15)
project(QuestionMark)

set(CMAKE_CXX_STANDARD 11)

add_executable(tests tests.cpp question_mark.hpp external/catch2.hpp)
