project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES)
set(SOURCE_FILES
        Entity/Multimedia.cpp Entity/Multimedia.h Entity/Video.cpp Entity/Video.h)


# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )