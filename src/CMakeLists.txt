project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES RestServer/dto/StatusDto.h RestServer/AppComponent.h RestServer/ErrorHandler.h RestServer/SwaggerComponent.h RestServer/Controller/ImageController.h RestServer/dto/output/ImageDTO.h RestServer/dto/output/MultimediaDto.h

        RestServer/dto/input/ImageCreationDto.h RestServer/dto/input/MultimediaInputDto.h)
set(SOURCE_FILES
        Entity/Impl/Multimedia.cpp
        Entity/Contract/Multimedia.h
        Entity/Impl/Video.cpp
        Entity/Contract/Video.h
        Entity/Impl/Audio.cpp
        Entity/Contract/Audio.h
        Entity/Impl/Image.cpp
        Entity/Contract/Image.h
        Shared/Tools.h
        Entity/Contract/IPlayable.h
        Entity/Impl/Playlist.cpp
        Entity/Contract/Playlist.h
        Shared/CustomError.h
        Entity/Impl/MediaDisplay.cpp
        Entity/Contract/MediaDisplay.h
        Entity/Contract/Parameter.h
        Entity/Impl/Parameter.cpp
        Entity/Contract/Schedule.h
        Entity/Impl/Schedule.cpp
        DataBase/Contracts/IRepository.h
        DataBase/Imp/DataBase.cpp
        DataBase/Contracts/DataBase.h
        DataBase/Imp/Repos/MultimediaRepo.cpp
        DataBase/Contracts/Repos/MultimediaRepo.h
        Entity/Contract/DependencyInjector.h
        DataBase/Imp/Repos/ImageRepo.cpp
        DataBase/Contracts/Repos/ImageRepo.h
        Shared/Timer.h
        MediaPlayer/VLC_Wrapper.cpp
        MediaPlayer/VLC_Wrapper.h
        Entity/Impl/MediaPlayingStates/Video/states/VideoStoppedState.cpp
        Entity/Contract/VideoState/VideoStoppedState.h
        Entity/Impl/MediaPlayingStates/Video/states/VideoPlayingState.cpp
        Entity/Contract/VideoState/VideoPlayingState.h
        Entity/Impl/MediaPlayingStates/Video/states/VideoPausedState.cpp
        Entity/Contract/VideoState/VideoPausedState.h
        Entity/Impl/MediaPlayingStates/Video/VideoStateHandler.cpp
        Entity/Contract/VideoState/VideoStateHandler.h
        Entity/Impl/MediaPlayingStates/Video/states/VideoTerminatedState.cpp
        Entity/Contract/VideoState/VideoTerminatedState.h

        DataBase/Contracts/Repos/Tools.h
        DataBase/Contracts/Repos/PlaylistRepo.h
        DataBase/Contracts/Repos/ScheduleRepo.h
        DataBase/Contracts/Repos/VideoRepo.h
        DataBase/Imp/Repos/PlaylistRepo.cpp
        DataBase/Imp/Repos/ScheduleRepo.cpp
        DataBase/Imp/Repos/VideoRepo.cpp

        )

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
        )