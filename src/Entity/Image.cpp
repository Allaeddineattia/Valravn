//
// Created by ismail on 7‏/11‏/2020.
//

#include "Image.h"

int Image::getId() const {
    return id;
}

const string &Image::getResolution() const {
    return resolution;
}

const unique_ptr<Multimedia> &Image::getMultimedia() const {
    return multimedia;
}

Image::Image(int id, const string &resolution, unique_ptr<Multimedia>multimedia) :
id(id),
resolution(resolution),
multimedia(move(multimedia))
{}
