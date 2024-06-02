cmake_minimum_required(VERSION 3.27)
project(mini_projet_magasin)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mini_projet_magasin
        liste.c
        liste.h
        main.c
        myconio.cpp
        myconio.h
        tableau.c)
