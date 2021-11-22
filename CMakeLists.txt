cmake_minimum_required(VERSION 3.17)
project(LinkedList__lab)

set(CMAKE_CXX_STANDARD 17)
include_directories(MyLinkedList Pair TestUI Exceptions)

add_executable(LinkedList__lab main.cpp
        MyLinkedList/MyLinkedList.h
        Pair/Pair.cpp
        Pair/Pair.h
        TestUI/TestUI.h
        Exceptions/ArgumentException.h)