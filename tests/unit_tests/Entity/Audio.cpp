//
// Created by ismail on 7‏/11‏/2020.
//

#include "Entity/Audio.h"
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"

TEST(Audio, Creation) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto audio = make_unique<Audio>(1, 13, move(multimedia));
    ASSERT_EQ(audio->getMultimedia()->getPath(),"path");
    ASSERT_EQ(audio->getMultimedia()->getMimeType(),"type");
}