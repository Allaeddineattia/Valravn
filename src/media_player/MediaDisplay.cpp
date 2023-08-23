//
// Created by alro on 21‏/11‏/2020.
//

#include <vector>
#include <media_player/MediaDisplay.h>


IPlayable & MediaDisplay::get_playable()  {
    return *playable;
}

Parameter & MediaDisplay::get_parameter() {
    return *parameter;
}

MediaDisplay::MediaDisplay(unique_ptr<IPlayable> playable, unique_ptr<Parameter> parameter) : playable(move(playable)), parameter(move(parameter)) {}

