//
// Created by ismail on 7‏/11‏/2020.
//

#include <audio/Audio.h>
#include <core/Error.h>

Audio::Audio(int id, int duration ,unique_ptr<Multimedia> multimedia) :
id(id),
duration(duration),
multimedia(std::move(multimedia)){}

int Audio::get_id() const {
    return id;
}

int Audio::get_duration() const {
    return duration;
}

const unique_ptr<Multimedia> &Audio::get_multimedia() const {
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


