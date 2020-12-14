//
// Created by alro on 14‏/12‏/2020.
//
#include "gtest/gtest.h"
#include "Entity/Multimedia.h"
#include "Entity/Video.h"
TEST(VideoPlaying, Play){
    auto multimedia = make_unique<Multimedia>(1, "video_path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140:150" );
    video->stop();
    video->pause();
    video->play();
    video->pause();
    video->play();
    video->stop();
    video->play();
    video->pause();
    video->stop();


}

