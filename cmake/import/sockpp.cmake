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

target_link_libraries(MeySQL sockpp)
add_dependencies(MeySQL sockppDownload)