//
// Created by ismail on 7‏/11‏/2020.
//


#include "Entity/Image.h"
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"

TEST(Image, Creation) {
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto image = make_unique<Image>(1, "140*80", move(multimedia));
}
