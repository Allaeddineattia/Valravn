//
// Created by alro on 21‏/11‏/2020.
//

#include <media_player/Parameter.h>

Parameter::Parameter(bool fullscreen, int volume, int timeout, float speed) :
    fullscreen(fullscreen), volume(volume), timeout(timeout), speed(speed) {}

bool Parameter::is_fullscreen() const {
    return fullscreen;
}

int Parameter::get_volume() const {
    return volume;
}

int Parameter::get_timeout() const {
    return timeout;
}

float Parameter::get_speed() const {
    return speed;
}
