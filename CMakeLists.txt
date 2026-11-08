cmake_minimum_required(VERSION 3.10)
project(vole_machine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(vole_machine
        main.cpp
        ALU.cpp
        CPU.cpp
        Memory.cpp
        Register.cpp
        VoleMachine.cpp
        UI.cpp)