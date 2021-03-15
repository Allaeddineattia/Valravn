include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS )
find_package(Boost COMPONENTS filesystem system REQUIRED)
#find_package(SQLite3 REQUIRED)
find_package(LIBVLC REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_executable(Unit_Tests_run
        test_example.cpp
        Entity/Multimedia.cpp
        Entity/Video.cpp
        Entity/Audio.cpp
        Entity/Image.cpp
        Entity/Playlist.cpp
        Entity/Parameter.cpp
        Entity/Tools.cpp
        Repo/image/SaveImage.cpp
        Repo/stubs/Images.h
        Repo/stubs/Images.cpp
        Repo/tools/Database.h
        Repo/tools/Database.cpp Repo/image/UpdateImage.cpp Repo/image/DeleteImage.cpp MediaPlaying/Video/VideoPlaying.cpp Repo/tools.cpp)

target_link_libraries(Unit_Tests_run gtest gtest_main)
target_link_libraries(Unit_Tests_run ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries (Unit_Tests_run ${Boost_SYSTEM_LIBRARY})
target_link_libraries (Unit_Tests_run ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries (Unit_Tests_run ${LIBVLC_LIBRARY})
target_link_libraries (Unit_Tests_run ${SQLITE3_LIBRARY})