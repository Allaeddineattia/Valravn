//
// Created by alro on 21‏/11‏/2020.
//

#ifndef VALRAVEN_MEDIADISPLAY_H
#define VALRAVEN_MEDIADISPLAY_H

#include <memory>
#include <media_player/IPlayable.h>
#include <media_player/Parameter.h>
using namespace std;

class MediaDisplay {
private:
    unique_ptr<IPlayable> playable;
    unique_ptr<Parameter> parameter;

public:
    MediaDisplay(unique_ptr<IPlayable> playable, unique_ptr<Parameter> parameter);

    IPlayable & get_playable();

    Parameter & get_parameter();
};


#endif //VALRAVEN_MEDIADISPLAY_H
