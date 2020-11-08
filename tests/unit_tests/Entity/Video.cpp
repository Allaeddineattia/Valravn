//
// Created by alro on 18‏/10‏/2020.
//
#include "gtest/gtest.h"

#include "Entity/Multimedia.h"
#include "Entity/Video.h"
TEST(Video, Creation){
    auto multimedia = make_unique<Multimedia>(1, "path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140*150" );
}

