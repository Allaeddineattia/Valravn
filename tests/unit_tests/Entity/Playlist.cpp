//
// Created by ismail on 19‏/11‏/2020.
//
#include "gtest/gtest.h"
#include <Entity/Image.h>
#include <Entity/Audio.h>
#include <Entity/Playlist.h>
#include "Entity/Video.h"
#include <memory>
using namespace std ;

TEST(Playlist,ThrowErrorOnInvalidadd) {

    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1, 5, move(multimedia), "140:80");
    auto image = make_unique<Image>(1, "140:80", move(multimedia));
    auto audio = make_unique<Audio>(1, 5, move(multimedia));
    vector<unique_ptr<Playabale>> dataplaylist ;
    auto playlist = make_unique<Playlist>( move(dataplaylist) ,1);

    playlist->addPlayabal(move(video));
    playlist->addPlayabal(move(audio));

    ASSERT_THROW(playlist->addPlayabal(move(video)),invalid_argument) ;
}
TEST(Playlist,ThrowErrorOnInvalidremove) {

    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1, 5, move(multimedia), "140:80");
    auto image = make_unique<Image>(1, "140:80", move(multimedia));
    auto audio = make_unique<Audio>(1, 5, move(multimedia));
    vector<unique_ptr<Playabale>> dataplaylist ;
    auto playlist = make_unique<Playlist>( move(dataplaylist) ,1);

    playlist->addPlayabal(move(video));
    playlist->addPlayabal(move(audio));

    ASSERT_THROW(playlist->removePlayabal(move(image)),invalid_argument) ;
}