//
// Created by alro on 18‏/10‏/2020.
//
#include "gtest/gtest.h"
#include "Entity/Contract/Multimedia.h"
#include "Entity/Contract/Video.h"
#include "Shared/CustomError.h"
TEST(Video, ThrowErrorOnInvalidResolution1){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW(make_unique<Video>(1 , 5 , move (multimedia) ,"a140:150"), invalid_argument);
}

TEST(Video, ThrowErrorOnInvalidResolution2){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW(make_unique<Video>(1 , 5 , move (multimedia) ,"140150"), invalid_argument);
}

TEST(Video, Creation){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140:150" );
    ASSERT_EQ(video->getMultimedia().getPath(),"path");
    ASSERT_EQ(video->getMultimedia().getMimeType(),"type");
    ASSERT_EQ(video->getResolution(),"140:150");
}

TEST(Video, ThrowErrorOnInvalidResolution3){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    ASSERT_THROW(make_unique<Video>(1 , 5 , move (multimedia) ," :140150"), invalid_argument);
}
