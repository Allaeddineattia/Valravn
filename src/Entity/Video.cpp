//
// Created by ismail on 7‏/11‏/2020.
//

#include "Video.h"

Video::Video(int id, int duration,  unique_ptr<Multimedia> multimedia, const string &resolution) :
id(id),
duration(duration),
multimedia(move(multimedia)),
resolution(resolution){}

int Video::getId() const {
    return id;
}

int Video::getDuration() const {
    return duration;
}

const unique_ptr<Multimedia> &Video::getMultimedia() const {
    return multimedia;
}

const string &Video::getResolution() const {
    return resolution;
}

