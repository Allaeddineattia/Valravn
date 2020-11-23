//
// Created by alro on 21‏/11‏/2020.
//

#include "Parameter.h"

Parameter::Parameter(bool fullscreen, int volume, int timeout, float speed) :
    fullscreen(fullscreen), volume(volume), timeout(timeout), speed(speed) {}

bool Parameter::isFullscreen() const {
    return fullscreen;
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
