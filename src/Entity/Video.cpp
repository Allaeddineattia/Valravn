//
// Created by alro on 18‏/10‏/2020.
//

#include "Video.h"

Video::Video(unique_ptr<Multimedia> multimedia)  {
    this->multimedia = move(multimedia);
}

const Multimedia &Video::getMultimedia() const {
    return *multimedia;
}
