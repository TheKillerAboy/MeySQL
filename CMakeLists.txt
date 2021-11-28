cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

### different compiler handle

if(DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
endif()
if(DEFINED ENV{CXX})
    set(CMAKE_CXX_COMPILER $ENV{CXX})
endif()

message("Using ${CMAKE_C_COMPILER} for CC")
message("Using ${CMAKE_CXX_COMPILER} for CXX")

###

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/thirdparty)

include(ExternalProject)

add_executable(
    MeySQL

    src/main.cpp
    src/rowcell.cpp
    src/connection.cpp
    src/server.cpp
)

### sockpp import

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

target_link_libraries(MeySQL sockpp)
add_dependencies(MeySQL sockppDownload)

### 

### boost import

ExternalProject_Add(boostDownload
    GIT_REPOSITORY git@github.com:boostorg/boost
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

SET(BOOST_INCLUDE_DIR ${EXTERNAL_INSTALL_LOCATION}/include)
SET(BOOST_LIB_DIR ${EXTERNAL_INSTALL_LOCATION}/lib)

add_library(boost SHARED IMPORTED)
# TODO: make set_target_properties for libs platform independant
set_target_properties(boost PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libsockpp.dylib)

include_directories(${boost_INCLUDE_DIR})

target_link_libraries(MeySQL boost)
add_dependencies(MeySQL boostDownload)

###

### listing port

set(PORT 8080)

###

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

### error checking flag handling

if($ENV{ENABLE_BUILD_ERROR_FLAGS})
    if(MSVC)
    target_compile_options(MeySQL PRIVATE /W4 /WX)
    else()
    target_compile_options(MeySQL PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

###