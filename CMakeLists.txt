cmake_minimum_required(VERSION 3.21.4)

project(MeySQL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

add_library(
    MeySQL SHARED
    
    src/rowcell.cpp
    src/row.cpp
    src/rowschema.cpp
    src/table.cpp
    src/cursor.cpp
)

set_target_properties(
    MeySQL PROPERTIES 
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER api/MeySQL.h
)
configure_file(MeySQL.pc.in MeySQL.pc @ONLY)

configure_file(
    include/MeySQLConfig.h.in
    include/MeySQLConfig.h
)

target_include_directories(MeySQL PRIVATE include)
target_include_directories(MeySQL PRIVATE src)

install(
    TARGETS MeySQL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES ${CMAKE_BINARY_DIR}/MeySQL.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)