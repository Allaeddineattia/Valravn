project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES)
set(SOURCE_FILES
        Entity/Multimedia.cpp
        Entity/Multimedia.h
        Entity/Video.cpp
        Entity/Video.h
        Entity/Audio.cpp
        Entity/Audio.h
        Entity/Image.cpp
        Entity/Image.h
        Shared/Tools.h
        Entity/IPlayable.h
        Entity/Playlist.cpp
        Entity/Playlist.h
        Shared/CustomError.h
        Entity/MediaDisplay.cpp
        Entity/MediaDisplay.h
        Entity/Parameter.h
        Entity/Parameter.cpp
        Entity/Schedule.h
        Entity/Schedule.cpp
        DataBase/Contracts/IRepository.h
        DataBase/Imp/DataBase.cpp
        DataBase/Contracts/DataBase.h
        DataBase/Imp/Repos/MultimediaRepo.cpp
        DataBase/Contracts/Repos/MultimediaRepo.h
        Entity/DependencyInjector.h
        DataBase/Imp/Repos/ImageRepo.cpp
        DataBase/Contracts/Repos/ImageRepo.h)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )