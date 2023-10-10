cmake_minimum_required(VERSION 3.27)
project(sqlymspell C)

set(CMAKE_C_STANDARD 11)

add_executable(sqlymspell main.c
        helpers.h
        editDistance.h
)
