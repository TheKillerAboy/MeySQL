cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(
    MeySQL SHARED
    src/rowcell.cpp
)

set_target_properties(
    MeySQL PROPERTIES 
    PUBLIC_HEADER include/MeySQL.h
)

configure_file(
    include/MeySQLConfig.h.in
    include/MeySQLConfig.h
)

target_include_directories(
    MeySQL PUBLIC
    ${PROJECT_BINARY_DIR}
)

target_include_directories(
    MeySQL PRIVATE
    include
)

target_include_directories(
    MeySQL PRIVATE
    src
)

include(GNUInstallDirs)

install(
    TARGETS MeySQL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)