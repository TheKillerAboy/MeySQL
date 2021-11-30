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
    src/connectionrequests.cpp
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

include_directories(${boost_INCLUDE_DIR})

set(stacktrace_basic_LIBRARY ${BOOST_LIB_DIR}/libboost_stacktrace_basic.a)
add_library(boost::stacktrace_basic UNKNOWN IMPORTED)
set_target_properties(
    boost::stacktrace_basic PROPERTIES
    IMPORTED_LOCATION ${stacktrace_basic_LIBRARY}
)

set(fiber_numa_LIBRARY ${BOOST_LIB_DIR}/libboost_fiber_numa.a)
add_library(boost::fiber_numa UNKNOWN IMPORTED)
set_target_properties(
    boost::fiber_numa PROPERTIES
    IMPORTED_LOCATION ${fiber_numa_LIBRARY}
)

set(container_LIBRARY ${BOOST_LIB_DIR}/libboost_container.a)
add_library(boost::container UNKNOWN IMPORTED)
set_target_properties(
    boost::container PROPERTIES
    IMPORTED_LOCATION ${container_LIBRARY}
)

set(context_LIBRARY ${BOOST_LIB_DIR}/libboost_context.a)
add_library(boost::context UNKNOWN IMPORTED)
set_target_properties(
    boost::context PROPERTIES
    IMPORTED_LOCATION ${context_LIBRARY}
)

set(iostreams_LIBRARY ${BOOST_LIB_DIR}/libboost_iostreams.a)
add_library(boost::iostreams UNKNOWN IMPORTED)
set_target_properties(
    boost::iostreams PROPERTIES
    IMPORTED_LOCATION ${iostreams_LIBRARY}
)

set(thread_LIBRARY ${BOOST_LIB_DIR}/libboost_thread.a)
add_library(boost::thread UNKNOWN IMPORTED)
set_target_properties(
    boost::thread PROPERTIES
    IMPORTED_LOCATION ${thread_LIBRARY}
)

set(program_options_LIBRARY ${BOOST_LIB_DIR}/libboost_program_options.a)
add_library(boost::program_options UNKNOWN IMPORTED)
set_target_properties(
    boost::program_options PROPERTIES
    IMPORTED_LOCATION ${program_options_LIBRARY}
)

set(coroutine_LIBRARY ${BOOST_LIB_DIR}/libboost_coroutine.a)
add_library(boost::coroutine UNKNOWN IMPORTED)
set_target_properties(
    boost::coroutine PROPERTIES
    IMPORTED_LOCATION ${coroutine_LIBRARY}
)

set(timer_LIBRARY ${BOOST_LIB_DIR}/libboost_timer.a)
add_library(boost::timer UNKNOWN IMPORTED)
set_target_properties(
    boost::timer PROPERTIES
    IMPORTED_LOCATION ${timer_LIBRARY}
)

set(contract_LIBRARY ${BOOST_LIB_DIR}/libboost_contract.a)
add_library(boost::contract UNKNOWN IMPORTED)
set_target_properties(
    boost::contract PROPERTIES
    IMPORTED_LOCATION ${contract_LIBRARY}
)

set(type_erasure_LIBRARY ${BOOST_LIB_DIR}/libboost_type_erasure.a)
add_library(boost::type_erasure UNKNOWN IMPORTED)
set_target_properties(
    boost::type_erasure PROPERTIES
    IMPORTED_LOCATION ${type_erasure_LIBRARY}
)

set(log_setup_LIBRARY ${BOOST_LIB_DIR}/libboost_log_setup.a)
add_library(boost::log_setup UNKNOWN IMPORTED)
set_target_properties(
    boost::log_setup PROPERTIES
    IMPORTED_LOCATION ${log_setup_LIBRARY}
)

set(atomic_LIBRARY ${BOOST_LIB_DIR}/libboost_atomic.a)
add_library(boost::atomic UNKNOWN IMPORTED)
set_target_properties(
    boost::atomic PROPERTIES
    IMPORTED_LOCATION ${atomic_LIBRARY}
)

set(fiber_LIBRARY ${BOOST_LIB_DIR}/libboost_fiber.a)
add_library(boost::fiber UNKNOWN IMPORTED)
set_target_properties(
    boost::fiber PROPERTIES
    IMPORTED_LOCATION ${fiber_LIBRARY}
)

set(random_LIBRARY ${BOOST_LIB_DIR}/libboost_random.a)
add_library(boost::random UNKNOWN IMPORTED)
set_target_properties(
    boost::random PROPERTIES
    IMPORTED_LOCATION ${random_LIBRARY}
)

set(date_time_LIBRARY ${BOOST_LIB_DIR}/libboost_date_time.a)
add_library(boost::date_time UNKNOWN IMPORTED)
set_target_properties(
    boost::date_time PROPERTIES
    IMPORTED_LOCATION ${date_time_LIBRARY}
)

set(stacktrace_addr2line_LIBRARY ${BOOST_LIB_DIR}/libboost_stacktrace_addr2line.a)
add_library(boost::stacktrace_addr2line UNKNOWN IMPORTED)
set_target_properties(
    boost::stacktrace_addr2line PROPERTIES
    IMPORTED_LOCATION ${stacktrace_addr2line_LIBRARY}
)

set(test_exec_monitor_LIBRARY ${BOOST_LIB_DIR}/libboost_test_exec_monitor.a)
add_library(boost::test_exec_monitor UNKNOWN IMPORTED)
set_target_properties(
    boost::test_exec_monitor PROPERTIES
    IMPORTED_LOCATION ${test_exec_monitor_LIBRARY}
)

set(stacktrace_noop_LIBRARY ${BOOST_LIB_DIR}/libboost_stacktrace_noop.a)
add_library(boost::stacktrace_noop UNKNOWN IMPORTED)
set_target_properties(
    boost::stacktrace_noop PROPERTIES
    IMPORTED_LOCATION ${stacktrace_noop_LIBRARY}
)

set(exception_LIBRARY ${BOOST_LIB_DIR}/libboost_exception.a)
add_library(boost::exception UNKNOWN IMPORTED)
set_target_properties(
    boost::exception PROPERTIES
    IMPORTED_LOCATION ${exception_LIBRARY}
)

set(locale_LIBRARY ${BOOST_LIB_DIR}/libboost_locale.a)
add_library(boost::locale UNKNOWN IMPORTED)
set_target_properties(
    boost::locale PROPERTIES
    IMPORTED_LOCATION ${locale_LIBRARY}
)

set(prg_exec_monitor_LIBRARY ${BOOST_LIB_DIR}/libboost_prg_exec_monitor.a)
add_library(boost::prg_exec_monitor UNKNOWN IMPORTED)
set_target_properties(
    boost::prg_exec_monitor PROPERTIES
    IMPORTED_LOCATION ${prg_exec_monitor_LIBRARY}
)

set(wave_LIBRARY ${BOOST_LIB_DIR}/libboost_wave.a)
add_library(boost::wave UNKNOWN IMPORTED)
set_target_properties(
    boost::wave PROPERTIES
    IMPORTED_LOCATION ${wave_LIBRARY}
)

set(log_LIBRARY ${BOOST_LIB_DIR}/libboost_log.a)
add_library(boost::log UNKNOWN IMPORTED)
set_target_properties(
    boost::log PROPERTIES
    IMPORTED_LOCATION ${log_LIBRARY}
)

set(graph_LIBRARY ${BOOST_LIB_DIR}/libboost_graph.a)
add_library(boost::graph UNKNOWN IMPORTED)
set_target_properties(
    boost::graph PROPERTIES
    IMPORTED_LOCATION ${graph_LIBRARY}
)

set(nowide_LIBRARY ${BOOST_LIB_DIR}/libboost_nowide.a)
add_library(boost::nowide UNKNOWN IMPORTED)
set_target_properties(
    boost::nowide PROPERTIES
    IMPORTED_LOCATION ${nowide_LIBRARY}
)

set(wserialization_LIBRARY ${BOOST_LIB_DIR}/libboost_wserialization.a)
add_library(boost::wserialization UNKNOWN IMPORTED)
set_target_properties(
    boost::wserialization PROPERTIES
    IMPORTED_LOCATION ${wserialization_LIBRARY}
)

set(unit_test_framework_LIBRARY ${BOOST_LIB_DIR}/libboost_unit_test_framework.a)
add_library(boost::unit_test_framework UNKNOWN IMPORTED)
set_target_properties(
    boost::unit_test_framework PROPERTIES
    IMPORTED_LOCATION ${unit_test_framework_LIBRARY}
)

set(json_LIBRARY ${BOOST_LIB_DIR}/libboost_json.a)
add_library(boost::json UNKNOWN IMPORTED)
set_target_properties(
    boost::json PROPERTIES
    IMPORTED_LOCATION ${json_LIBRARY}
)

set(filesystem_LIBRARY ${BOOST_LIB_DIR}/libboost_filesystem.a)
add_library(boost::filesystem UNKNOWN IMPORTED)
set_target_properties(
    boost::filesystem PROPERTIES
    IMPORTED_LOCATION ${filesystem_LIBRARY}
)

set(chrono_LIBRARY ${BOOST_LIB_DIR}/libboost_chrono.a)
add_library(boost::chrono UNKNOWN IMPORTED)
set_target_properties(
    boost::chrono PROPERTIES
    IMPORTED_LOCATION ${chrono_LIBRARY}
)

set(serialization_LIBRARY ${BOOST_LIB_DIR}/libboost_serialization.a)
add_library(boost::serialization UNKNOWN IMPORTED)
set_target_properties(
    boost::serialization PROPERTIES
    IMPORTED_LOCATION ${serialization_LIBRARY}
)

add_library(boost INTERFACE IMPORTED)
set_property(
    TARGET boost PROPERTY
    INTERFACE_LINK_LIBRARIES 

    boost::stacktrace_basic 
    boost::fiber_numa 
    boost::container 
    boost::context 
    boost::iostreams 
    boost::thread 
    boost::program_options 
    boost::coroutine 
    boost::timer 
    boost::contract 
    boost::type_erasure 
    boost::log_setup 
    boost::atomic 
    boost::fiber 
    boost::random 
    boost::date_time 
    boost::stacktrace_addr2line 
    boost::test_exec_monitor 
    boost::stacktrace_noop 
    boost::exception 
    boost::locale 
    boost::prg_exec_monitor 
    boost::wave 
    boost::log 
    boost::graph 
    boost::nowide 
    boost::wserialization 
    boost::unit_test_framework 
    boost::json 
    boost::filesystem 
    boost::chrono 
    boost::serialization
)

target_link_libraries(MeySQL boost)
add_dependencies(MeySQL boostDownload)

#TODO Make boost import prettier or move
###

### listing port

set(PORT 8080)

set(ENV{PORT} $PORT)

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