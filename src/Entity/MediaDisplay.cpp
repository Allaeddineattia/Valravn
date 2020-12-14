//
// Created by alro on 21‏/11‏/2020.
//

#include <vector>
#include "MediaDisplay.h"


IPlayable & MediaDisplay::getPlayable()  {
    return *playable;
}

Parameter & MediaDisplay::getParameter() {
    return *parameter;
}

MediaDisplay::MediaDisplay(unique_ptr<IPlayable> playable, unique_ptr<Parameter> parameter) : playable(move(playable)), parameter(move(parameter)) {}

