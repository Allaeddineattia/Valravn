//
// Created by ismail on 7‏/11‏/2020.
//
#include<stdexcept>
#include <iostream>
#include <cmath>
#include "Video.h"
#include "Shared/Tools.h"
#include "Shared/CustomError.h"

using namespace std;
Video::Video(int id, int duration, unique_ptr<Multimedia> multimedia, string_view resolution_input) :
id(id),
duration(duration),
multimedia(move(multimedia)),
stateHandler(make_unique<VideoStateHandler>(*this))
{
    string vResolution = resolution_input.data();
    Tools::remove_blanks(vResolution);
    Tools::check_resolution_string_pattern(vResolution);
    this->resolution = resolution_input;
}

int Video::getId() const {
    return id;
}

int Video::getDuration() const {
    return duration;
}

const unique_ptr<Multimedia> &Video::getMultimedia() const {
    return multimedia;
}

string_view Video::getResolution() const {
    return resolution;
}

void Video::play() {
    stateHandler->play();
}

void Video::stop() {
    stateHandler->stop();
}

void Video::pause() {
    stateHandler->pause();
}

