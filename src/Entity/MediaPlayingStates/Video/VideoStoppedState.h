//
// Created by alro on 14‏/12‏/2020.
//

#ifndef MYPROJECT_VIDEOSTOPPEDSTATE_H
#define MYPROJECT_VIDEOSTOPPEDSTATE_H


#include <Entity/IPlayable.h>
#include <Entity/Video.h>
#include "VideoStateHandler.h"
class VideoStateHandler;

class VideoStoppedState: public IPlayable {
    VideoStateHandler & stateHandler;
public:
    VideoStoppedState(VideoStateHandler &stateHandler);

    void play() override;
    void stop() override;
    void pause() override;

};


#endif //MYPROJECT_VIDEOSTOPPEDSTATE_H
