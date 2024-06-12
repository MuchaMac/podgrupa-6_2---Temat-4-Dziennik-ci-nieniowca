cmake_minimum_required(VERSION 3.26)
project(projekt_npg)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(projekt_npg
        include/DC.hpp
        src/DC_JM.cpp
        src/DC_Kap.cpp
        src/DC_MM.cpp
        src/DC_WM.cpp
        main.cpp)
