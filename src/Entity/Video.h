//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_VIDEO_H
#define MYPROJECT_VIDEO_H
#include "Entity/Multimedia.h"
#include <stdio.h>
#include <string>
#include <memory>
class Video {
private:

    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;
    string resolution ;
public:
    int getId() const;

    int getDuration() const;

    const unique_ptr<Multimedia> &getMultimedia() const;

    const string &getResolution() const;

    Video(int id, int duration, unique_ptr<Multimedia> multimedia, const string &resolution);


};


#endif //MYPROJECT_VIDEO_H
