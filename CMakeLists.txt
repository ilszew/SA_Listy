cmake_minimum_required(VERSION 3.30)
project(SD_Listy)

set(CMAKE_CXX_STANDARD 20)

add_executable(SD_Listy main.cpp
        singlyLinkedList.h
        doublyLinkedList.h
        arrayList.h
        timer.h
        randomGenerator.h
        performanceTester.h)
