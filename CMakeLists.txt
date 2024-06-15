cmake_minimum_required(VERSION 3.28)
project(Kanishk_Compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kanishk_Compiler src/main.cpp
        src/tokenization.h
        src/parser.h
        src/generation.h
)
