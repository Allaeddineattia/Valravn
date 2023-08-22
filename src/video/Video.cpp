//
// Created by ismail on 7‏/11‏/2020.
//
#include<stdexcept>
#include <iostream>
#include <cmath>
#include <video/Video.h>
#include <core/StringTools.h>


using namespace std;
Video::Video(int id, int duration, unique_ptr<Multimedia> multimedia, string_view resolution_input) :
id(id),
duration(duration),
multimedia(std::move(multimedia))
{
    string vResolution = resolution_input.data();
    StringTools::remove_blanks(vResolution);
    StringTools::check_resolution_string_pattern(vResolution);
    this->resolution = resolution_input;
}

unsigned int Video::getId() const {
    return id;
}

int Video::getDuration() const {
    return duration;
}

const Multimedia  & Video::getMultimedia() const {
    return *multimedia;
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

void Video::setStateHandler(unique_ptr<VideoStateHandler> stateHandler) {
    Video::stateHandler = move(stateHandler);
}

