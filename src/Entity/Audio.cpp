//
// Created by ismail on 7‏/11‏/2020.
//

#include "Audio.h"

Audio::Audio(int id, int duration ,unique_ptr<Multimedia> multimedia) :
id(id),
duration(duration) ,
multimedia(move(multimedia)){}

int Audio::getId() const {
    return id;
}

int Audio::getDuration() const {
    return duration;
}

const unique_ptr<Multimedia> &Audio::getMultimedia() const {
    return multimedia;
}
