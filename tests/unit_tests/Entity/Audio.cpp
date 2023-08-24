//
// Created by ismail on 7‏/11‏/2020.
//


#include "gtest/gtest.h"
#include <core/Error.h>
#include <audio/Audio.h>
#include <media_player/Multimedia.h>

TEST(Audio, Creation) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_EQ(audio->get_multimedia()->getPath(), "path");
    ASSERT_EQ(audio->get_multimedia()->getMimeType(), "type");
}
TEST(Audio ,Throw_error_on_play_NotImplementedException){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_THROW(audio->play(),NotImplementedException);
}
TEST(Audio ,Throw_error_on_stop_NotImplementedException){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_THROW(audio->stop(),NotImplementedException);
}
TEST(Audio ,Throw_error_on_pause_NotImplementedException){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_THROW(audio->pause(),NotImplementedException);
}
