cmake_minimum_required(VERSION 3.13)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(HW1
        utils.h
        SLinkedList.h
        )

add_executable(HW1
        hw1.c
        )
