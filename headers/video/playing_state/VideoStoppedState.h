//
// Created by alro on 14‏/12‏/2020.
//

#ifndef VALRAVEN_VIDEOSTOPPEDSTATE_H
#define VALRAVEN_VIDEOSTOPPEDSTATE_H


#include <media_player/IPlayable.h>
#include <video/Video.h>
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


#endif //VALRAVEN_VIDEOSTOPPEDSTATE_H
