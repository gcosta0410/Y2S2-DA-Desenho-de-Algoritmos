cmake_minimum_required(VERSION 3.20)
project(DA_T2_G113)

set(CMAKE_CXX_STANDARD 14)

include_directories(codigo)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(DA_T2_G113
        input/in01_b.txt
        input/in02_b.txt
        input/in03_b.txt
        input/in04_b.txt
        input/in05_b.txt
        input/in06_b.txt
        input/in07_b.txt
        input/in08_b.txt
        input/in09_b.txt
        input/in10_b.txt
        main.cpp
        codigo/Menu.cpp
        codigo/Menu.h
        codigo/AuxiliaryFunctions.cpp
        codigo/AuxiliaryFunctions.h
        codigo/Ctcp.cpp
        codigo/Ctcp.h
        codigo/maxHeap.h
        codigo/EdmondsKarpGraph.cpp
        codigo/EdmondsKarpGraph.h)

