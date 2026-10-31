cmake_minimum_required(VERSION 4.1)
project(vole_machine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(vole_machine
        ALU.cpp
        ALU.h
        CPU.h
        main.cpp
        Memory.h
        Register.cpp
        Register.h
        UI.h
        VoleMachine.h
        UI.cpp)
