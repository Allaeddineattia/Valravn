project(${CMAKE_PROJECT_NAME}_lib)


set(SOURCE_FILES

        audio/Audio.cpp

        media_player/Multimedia.cpp
        media_player/MediaDisplay.cpp
        media_player/Parameter.cpp
        media_player/MultimediaRepo.cpp

        playlist/Playlist.cpp
        playlist/Schedule.cpp
        playlist/PlaylistRepo.cpp
        playlist/ScheduleRepo.cpp


        image/Image.cpp
        image/ImageRepo.cpp
        media_player/VLC_Wrapper.cpp

        video/Video.cpp
        video/VideoRepo.cpp
        video/VideoStateHandler.cpp

        video/states/VideoStoppedState.cpp
        video/states/VideoPlayingState.cpp
        video/states/VideoPausedState.cpp
        video/states/VideoTerminatedState.cpp



        database/SQLHelpers.cpp
        database/DataBase.cpp
)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )