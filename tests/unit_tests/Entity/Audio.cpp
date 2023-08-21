//
// Created by ismail on 7‏/11‏/2020.
//

#include "Entity/Contract/Audio.h"
#include "gtest/gtest.h"
#include "Shared/CustomError.h"
#include <media_player/Multimedia.h>

TEST(Audio, Creation) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_EQ(audio->getMultimedia()->getPath(),"path");
    ASSERT_EQ(audio->getMultimedia()->getMimeType(),"type");
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
