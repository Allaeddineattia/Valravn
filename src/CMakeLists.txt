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
        DataBase/Contracts/Repos/ImageRepo.h Shared/Timer.h MediaPlayer/VLC_Wrapper.cpp MediaPlayer/VLC_Wrapper.h Entity/MediaPlayingStates/Video/VideoStoppedState.cpp Entity/MediaPlayingStates/Video/VideoStoppedState.h Entity/MediaPlayingStates/Video/VideoPlayingState.cpp Entity/MediaPlayingStates/Video/VideoPlayingState.h Entity/MediaPlayingStates/Video/VideoPausedState.cpp Entity/MediaPlayingStates/Video/VideoPausedState.h Entity/MediaPlayingStates/Video/VideoStateHandler.cpp Entity/MediaPlayingStates/Video/VideoStateHandler.h DataBase/Contracts/Repos/VideoRepo.h DataBase/Imp/Repos/VideoRepo.cpp DataBase/Contracts/Repos/ScheduleRepo.h DataBase/Imp/Repos/ScheduleRepo.cpp)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )