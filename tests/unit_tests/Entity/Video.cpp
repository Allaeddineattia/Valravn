//
// Created by alro on 18‏/10‏/2020.
//
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"
#include "Entity/Video.h"
TEST(Video, CreationError1){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"a140:150" );
    ASSERT_EQ(video->getMultimedia()->getPath(),"path");
    ASSERT_EQ(video->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(video->getResolution(),"a140:150");
}

TEST(Video, CreationError2){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140150" );
    ASSERT_EQ(video->getMultimedia()->getPath(),"path");
    ASSERT_EQ(video->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(video->getResolution(),"140150");
}

TEST(Video, Creation){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140:150" );
    ASSERT_EQ(video->getMultimedia()->getPath(),"path");
    ASSERT_EQ(video->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(video->getResolution(),"140:150");

}
TEST(Video, CreationError3){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,":140150" );
    ASSERT_EQ(video->getMultimedia()->getPath(),"path");
    ASSERT_EQ(video->getMultimedia()->getMimeType(),"type");
    ASSERT_EQ(video->getResolution(),":140150");
}