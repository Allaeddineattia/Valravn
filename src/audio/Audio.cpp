//
// Created by ismail on 7‏/11‏/2020.
//

#include <audio/Audio.h>
#include <core/Error.h>

Audio::Audio(int id, int duration ,unique_ptr<Multimedia> multimedia) :
id(id),
duration(duration),
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



void Audio::play() {
    throw NotImplementedException();
}

void Audio::stop() {
    throw NotImplementedException();
}

void Audio::pause() {
    throw NotImplementedException();
}


