//
// Created by alro on 21‏/11‏/2020.
//

#include <vector>
#include "MediaDisplay.h"


IPlayable & MediaDisplay::getPlayabale()  {
    return *playable;
}

Parameter & MediaDisplay::getParameter() {
    return *parameter;
}

MediaDisplay::MediaDisplay(unique_ptr<IPlayable> playabale, unique_ptr<Parameter> parameter) : playable(move(playabale)), parameter(move(parameter)) {}

