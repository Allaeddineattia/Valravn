//
// Created by ismail on 7‏/11‏/2020.
//
#include<string_view>
#include "Tools.h"
#include "Image.h"

Image::Image(int id, string_view resolution_input, unique_ptr<Multimedia>multimedia) :
             id(id), multimedia(move(multimedia))
{
    string vResolution = resolution_input.data();
    Tools::remove_blanks(vResolution);
    Tools::check_resolution_string_pattern(vResolution);
    this->resolution = resolution_input;
}

int Image::getId() const {
    return id;
}

string_view Image::getResolution() const {
    return resolution;
}

const unique_ptr<Multimedia> &Image::getMultimedia() const {
    return multimedia;
}


