//
// Created by ismail on 7‏/11‏/2020.
//
#include<string_view>
#include <core/Tools.h>
#include <core/StringTools.h>
#include <image/Image.h>
#include <core/Error.h>


Image::Image(int id, string_view resolution_input, unique_ptr<Multimedia>multimedia) :
             id(id), multimedia(move(multimedia))
{
    string vResolution = resolution_input.data();
    StringTools::remove_blanks(vResolution);
    StringTools::check_resolution_string_pattern(vResolution);
    this->resolution = resolution_input;
}

unsigned int Image::get_id() const {
    return id;
}

string_view Image::get_resolution() const {
    return resolution;
}

const Multimedia &Image::get_multimedia() const {
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





