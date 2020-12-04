//
// Created by ismail on 7‏/11‏/2020.
//
#include<string_view>
#include "Shared/Tools.h"
#include "Image.h"
#include "Shared/CustomError.h"


Image::Image(int id, string_view resolution_input, unique_ptr<Multimedia>multimedia) :
             id(id), multimedia(move(multimedia))
{
    string vResolution = resolution_input.data();
    Tools::remove_blanks(vResolution);
    Tools::check_resolution_string_pattern(vResolution);
    this->resolution = resolution_input;
}

unsigned int Image::getId() const {
    return id;
}

string_view Image::getResolution() const {
    return resolution;
}

const Multimedia &Image::getMultimedia() const {
    return *multimedia;
}

void Image::play() {
    throw NotImplementedException();
}

void Image::pause() {
    throw NotImplementedException();
}

void Image::stop() {
    throw NotImplementedException();
}


bool Image::operator==(const Image &rhs) const {
    return *multimedia == *(rhs.multimedia)&&
           this->resolution == rhs.resolution;
}





