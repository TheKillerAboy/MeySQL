cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

if(DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
endif()
if(DEFINED ENV{CXX})
    set(CMAKE_CXX_COMPILER $ENV{CXX})
endif()

message("Using ${CMAKE_C_COMPILER} for CC")
message("Using ${CMAKE_CXX_COMPILER} for CXX")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/thirdparty)

include(ExternalProject)

ExternalProject_Add(sockppDownload
    GIT_REPOSITORY https://github.com/fpagliughi/sockpp
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

SET(SOCKPP_INCLUDE_DIR ${EXTERNAL_INSTALL_LOCATION}/include)
SET(SOCKPP_LIB_DIR ${EXTERNAL_INSTALL_LOCATION}/lib)

add_library(sockpp SHARED IMPORTED)
# TODO: make set_target_properties for libs platform independant
set_target_properties(sockpp PROPERTIES IMPORTED_LOCATION ${SOCKPP_LIB_DIR}/libsockpp.dylib)

include_directories(${SOCKPP_INCLUDE_DIR})

add_executable(
    MeySQL

    src/main.cpp
    src/rowcell.cpp
    src/connection.cpp
    src/server.cpp
)
target_link_libraries(MeySQL sockpp)
add_dependencies(MeySQL sockppDownload)

set(PORT 8080)

configure_file(
    include/MeySQLConfig.h.in
    include/MeySQLConfig.h
)

target_include_directories(
    MeySQL PRIVATE
    include
)
target_include_directories(
    MeySQL PUBLIC
    ${PROJECT_BINARY_DIR}/include
)