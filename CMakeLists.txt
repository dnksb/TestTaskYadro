cmake_minimum_required(VERSION 3.16)
project(test_task)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_task main.cpp ./table/table.cpp ./time/time.cpp ./client/client.cpp)

