//
// Created by ismail on 19‏/11‏/2020.
//
#include "gtest/gtest.h"
#include <image/Image.h>
#include <Entity/Contract/Audio.h>
#include <Entity/Contract/Playlist.h>
#include <video/Video.h>
#include <memory>
using namespace std ;


TEST(Playlist,ThrowErrorOnInvalidromve) {
    auto playlist = make_unique<Playlist>( 1);
    auto multimedia = make_unique<Multimedia>(2, "path", 50, "type");
    auto video = make_unique<Video>(1, 5, move(multimedia), "140:100");
    auto parameter =make_unique<Parameter>(true, 20, 20, 50);
    auto mediaDisplay = make_unique<MediaDisplay>(move(video),move(parameter));
    playlist->addMediaDisplay(move(mediaDisplay));
    ASSERT_THROW(playlist->removePlayable(1), invalid_argument);
}
