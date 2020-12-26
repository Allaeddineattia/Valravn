//
// Created by alro on 21‏/11‏/2020.
//

#include "Parameter.h"

Parameter::Parameter(int id , bool fullscreen, int volume, int timeout, float speed) :
    id(id), fullscreen(fullscreen), volume(volume), timeout(timeout), speed(speed)  {}

bool Parameter::isFullscreen() const {
    return fullscreen;
}
unsigned int Parameter::GetId() const {
    return id;
}
int Parameter::getVolume() const {
    return volume;
}

int Parameter::getTimeout() const {
    return timeout;
}

float Parameter::getSpeed() const {
    return speed;
}
