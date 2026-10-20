cmake_minimum_required(VERSION 4.3)
project(OrderBook)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OrderBook
        OrderBook.cpp
        OrderBook.h
        main.cpp)
