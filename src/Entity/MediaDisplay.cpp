//
// Created by alro on 21‏/11‏/2020.
//

#include "MediaDisplay.h"

MediaDisplay::MediaDisplay(unique_ptr<Playabale> playabale, unique_ptr<Parameter> parameter) : playabale(
        move(playabale)), parameter(move(parameter)) {}

const unique_ptr<Playabale> &MediaDisplay::getPlayabale() const {
    return playabale;
}

const unique_ptr<Parameter> &MediaDisplay::getParameter() const {
    return parameter;
}
