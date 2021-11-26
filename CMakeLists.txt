cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    MeySQL SHARED

    src/main.cpp
    src/rowcell.cpp
)

configure_file(
    include/MeySQLConfig.h.in
    include/MeySQLConfig.h
)

target_include_directories(
    MeySQL PRIVATE
    include
)