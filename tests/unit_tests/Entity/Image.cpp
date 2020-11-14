//
// Created by ismail on 7‏/11‏/2020.
//


#include "Entity/Image.h"
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"

TEST(Image, ThrowErrorOnInvalidResolution1) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW(make_unique<Image>(1, "a140:80", move(multimedia)), invalid_argument);
}

TEST(Image, ThrowErrorOnInvalidResolution2) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW( make_unique<Image>(1, "14080", move(multimedia)), invalid_argument);

}

TEST(Image, CreationImage) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto image = make_unique<Image>(1, " 140:800", move(multimedia));
    ASSERT_EQ(image->getMultimedia()->getPath(),"path");
    ASSERT_EQ(image->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(image->getResolution()," 140:800");

}

TEST(Image, ThrowErrorOnInvalidResolution3) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW( make_unique<Image>(1, " :140:80", move(multimedia)), invalid_argument);

}

TEST(Image, ThrowErrorOnInvalidResolution4) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW( make_unique<Image>(1, "140:80", move(multimedia)), invalid_argument);
}