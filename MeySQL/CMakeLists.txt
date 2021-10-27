cmake_minimum_required(VERSION 3.10)

# set the project name
project(MeySQL VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# add the executable
#add_executable(MeySQL main.cpp)

set(MY_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/headers/include)
set(MY_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

#include headers
#header_files_block begin
set(
	HEADER_FILES
	${MY_INCLUDES_DIR}/mapnode.h
	${MY_INCLUDES_DIR}/tableheader.h
	${MY_INCLUDES_DIR}/database.h
	${MY_INCLUDES_DIR}/pointerarray.h
	${MY_INCLUDES_DIR}/cellarray.h
	${MY_INCLUDES_DIR}/generatorlist.h
	${MY_INCLUDES_DIR}/cell.h
	${MY_INCLUDES_DIR}/utils.h
	${MY_INCLUDES_DIR}/table.h
	${MY_INCLUDES_DIR}/recordlist.h
	${MY_INCLUDES_DIR}/map.h
	${MY_INCLUDES_DIR}/tablelist.h
	${MY_INCLUDES_DIR}/list.h
	${MY_INCLUDES_DIR}/record.h
	${MY_INCLUDES_DIR}/cursor.h
	${MY_INCLUDES_DIR}/tablelink.h
	${MY_INCLUDES_DIR}/generator.h
	${MY_INCLUDES_DIR}/listnode.h
	${MY_INCLUDES_DIR}/tablelinklist.h
)
#header_files_block end

#include source files
#src_files_block begin
set(
	SOURCE_FILES
	${MY_SRC_DIR}/tmp.cpp
)
#src_files_block end

#create library
add_library(
	MeySQL 
	SHARED ${SOURCE_FILES} ${HEADER_FILES}
)

#include header include directory
target_include_directories(
	MeySQL
	PUBLIC ${MY_INCLUDES_DIR}
)
include_directories(
	${MY_INCLUDES_DIR}
)
target_include_directories(
	MeySQL 
	PUBLIC "${PROJECT_BINARY_DIR}"
)

#setup config header file
configure_file(
	${MY_INCLUDES_DIR}/MeySQLConfig.h.in MeySQLConfig.h
)

#setup version control
set_target_properties(
	MeySQL 
	PROPERTIES VERSION ${PROJECT_VERSION}
)
set_target_properties(
	MeySQL 
	PROPERTIES SOVERSION 1
)

#setup install instructions
include(GNUInstallDirs)
install(
	TARGETS MeySQL
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
	FILES ${CMAKE_BINARY_DIR}/MeySQLConfig.h
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
