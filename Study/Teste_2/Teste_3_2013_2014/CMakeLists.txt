cmake_minimum_required(VERSION 3.17)
project(Teste_3_2013_2014)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Teste_3_2013_2014
        BST.h
        Cooperativa.cpp
        Cooperativa.h
        Test.cpp)
