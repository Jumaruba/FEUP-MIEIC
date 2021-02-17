cmake_minimum_required(VERSION 3.15)
project(AEDA_Proj1)

set(CMAKE_CXX_STANDARD 14)

add_executable(AEDA_Proj1 main.cpp Source/Empresa.cpp Source/Camiao.cpp Header/Camiao.h Source/Clientes.cpp Header/Empresa.h Source/Servicos.cpp Source/Local.cpp Source/TaxTable.cpp Header/Servicos.h Source/utils.cpp Header/utils.h Source/Motorista.cpp Header/Motorista.h
        Header/Workshop.h Source/Workshop.cpp Source/Date.cpp Header/Date.h)
