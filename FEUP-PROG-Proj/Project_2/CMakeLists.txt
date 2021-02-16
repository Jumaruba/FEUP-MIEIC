cmake_minimum_required(VERSION 3.13)
project(project_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_2 main.cpp data.cpp data.h aux.h aux.cpp clients.cpp clients.h menu.cpp menu.h packs.cpp packs.h agency.cpp agency.h)