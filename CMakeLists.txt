cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/thirdparty)

include(ExternalProject)

ExternalProject_Add(sockpp
    GIT_REPOSITORY https://github.com/fpagliughi/sockpp
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(
    MeySQL

    src/main.cpp
    src/rowcell.cpp
    src/connection.cpp
    src/server.cpp
)

set(PORT 8080)

configure_file(
    include/MeySQLConfig.h.in
    include/MeySQLConfig.h
)

target_include_directories(
    MeySQL PRIVATE
    include
)