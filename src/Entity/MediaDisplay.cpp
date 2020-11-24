//
// Created by alro on 21‏/11‏/2020.
//

#include <vector>
#include "MediaDisplay.h"


Playabale & MediaDisplay::getPlayabale()  {
    return *playabale;
}

Parameter & MediaDisplay::getParameter() {
    return *parameter;
}

MediaDisplay::MediaDisplay(unique_ptr<Playabale> playabale,  unique_ptr<Parameter> parameter) : playabale(move(playabale)), parameter(move(parameter)) {}

