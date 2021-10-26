cmake_minimum_required(VERSION 3.10)

# set the project name
project(TEST VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# add the executable
#add_executable(MeySQL main.cpp)

set(MY_INCLUDES ${PROJECT_SOURCE_DIR}/headers/include)

target_link_libraries(MeySQL PUBLIC ${EXTRA_LIBS})

target_include_directories(
	TEST PUBLIC
	"${PROJECT_BINARY_DIR}"
)

configure_file(${MY_INCLUDES}/MeySQLConfig.h.in MeySQLConfig.h)
