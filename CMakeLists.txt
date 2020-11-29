cmake_minimum_required(VERSION 3.9)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS )
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(LIBVLC REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})


include_directories(src)




add_subdirectory(src)
add_subdirectory(tests)



# Doxygen Build
option(BUILD_DOC "Build Documentation" ON)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen buld started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries (${CMAKE_PROJECT_NAME}_run ${Boost_SYSTEM_LIBRARY})
target_link_libraries (${CMAKE_PROJECT_NAME}_run ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries (${CMAKE_PROJECT_NAME}_run ${LIBVLC_LIBRARY})
target_link_libraries (${CMAKE_PROJECT_NAME}_run ${SQLITE3_LIBRARY})