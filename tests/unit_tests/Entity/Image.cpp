//
// Created by ismail on 7‏/11‏/2020.
//


#include "Entity/Image.h"
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"

TEST(Image, CreationError1) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto image = make_unique<Image>(1, "a140:80", move(multimedia));
    ASSERT_EQ(image->getMultimedia()->getPath(),"path");
    ASSERT_EQ(image->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(image->getResolution(),"a140:80");
}
TEST(Image, CreationError2) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto image = make_unique<Image>(1, "14080", move(multimedia));
    ASSERT_EQ(image->getMultimedia()->getPath(),"path");
    ASSERT_EQ(image->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(image->getResolution(),"14080");
}
TEST(Image, Creation) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto image = make_unique<Image>(1, "140:80", move(multimedia));
    ASSERT_EQ(image->getMultimedia()->getPath(),"path");
    ASSERT_EQ(image->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(image->getResolution(),"140:80");
}