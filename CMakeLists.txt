cmake_minimum_required(VERSION 3.30)
project(MASM_2_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(MASM_2_0 main.cpp
        Array.h
        Array.cpp
        String.h
        String.cpp
        Debugger.h
        Debugger.cpp
        Instructions.h
        Instructions.cpp
        Math.h
        Math.cpp
        Memory.h
        Memory.cpp
        Register.h
        Register.cpp)
