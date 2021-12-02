cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

include(cmake/envcheck.cmake)

cxxcompile_check()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/thirdparty)

add_executable(
    MeySQL

    src/main.cpp
    src/rowcell.cpp
    src/connection.cpp
    src/server.cpp
    src/connectionrequests.cpp
)

### imports
include(cmake/import/sockpp.cmake)
include(cmake/import/boost.cmake)
###

### listing port
if(NOT DEFINED ENV{MEYSQL_PORT})
    set(ENV{MEYSQL_PORT} 5332)
endif()

set(PORT $ENV{MEYSQL_PORT})
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