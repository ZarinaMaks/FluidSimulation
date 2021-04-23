cmake_minimum_required(VERSION 3.17)
project(FioLib-Test)

set(CMAKE_CXX_STANDARD 17)

include_directories(FioLib/headers)
include_directories(FluidLib/headers)
add_executable(FioLib-Test FioLib/source/test.cpp
        FluidLib/source/basic.cpp
        FluidLib/source/borders2d.cpp
        FluidLib/source/components2d.cpp
        FluidLib/source/exception.cpp
        FluidLib/source/fluidlib2d.cpp
        FluidLib/source/fluids2d.cpp
        FluidLib/source/tools2d.cpp)
