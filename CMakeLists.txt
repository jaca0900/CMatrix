cmake_minimum_required(VERSION 3.14)
project(CMatrix_master)

set(CMAKE_CXX_STANDARD 14)

add_executable(CMatrix_master
    main.cpp
    components/CMatrix.cpp
    components/CMatrix.h)
