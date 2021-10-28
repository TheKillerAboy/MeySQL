cmake_minimum_required(VERSION 3.10)

# set the project name
project(TEST VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../../MeySQL ../../build)
list(APPEND EXTRA_SHARED_LIBS libMeySQL.so)

# add the executable
add_executable(TEST main.cpp)

#target_link_libraries(TEST PUBLIC ${EXTRA_LIBS})
target_link_libraries(TEST ${EXTRA_SHARED_LIBS})

target_include_directories(
	TEST PUBLIC
	"${PROJECT_BINARY_DIR}"
)
