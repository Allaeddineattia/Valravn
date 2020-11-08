project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES)
set(SOURCE_FILES
        Entity/Multimedia.cpp Entity/Multimedia.h Entity/Video.cpp Entity/Video.h Entity/Audio.cpp  Entity/Audio.h Entity/Image.cpp Entity/Image.h
)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )