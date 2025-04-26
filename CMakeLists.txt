cmake_minimum_required(VERSION 3.30)
project(ProjektVol2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjektVol2 main.cpp
        Task.cpp
        Task.h
        TodoListManager.cpp
        TodoListManager.h)
