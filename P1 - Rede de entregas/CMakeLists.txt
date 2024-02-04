cmake_minimum_required(VERSION 3.20)
project(DA_T1_G113)

set(CMAKE_CXX_STANDARD 14)

include_directories(codigo)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(DA_T1_G113
        input/carrinhas.txt
        input/encomendas.txt
        main.cpp
        codigo/Menu.cpp
        codigo/Menu.h
        codigo/Order.cpp
        codigo/Order.h
        codigo/Van.cpp
        codigo/Van.h
        codigo/AuxiliaryFunctions.cpp
        codigo/AuxiliaryFunctions.h
        codigo/DeliveryService.cpp
        codigo/DeliveryService.h
        codigo/Courier.cpp
        codigo/Courier.h
        )

