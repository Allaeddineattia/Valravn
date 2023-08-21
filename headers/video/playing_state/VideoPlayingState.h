//
// Created by alro on 14‏/12‏/2020.
//

#ifndef VALRAVEN_VIDEOPLAYINGSTATE_H
#define VALRAVEN_VIDEOPLAYINGSTATE_H


#include <media_player/IPlayable.h>
#include <video/Video.h>
#include "VideoStateHandler.h"

class VideoStateHandler;

class VideoPlayingState: public IPlayable  {
    VideoStateHandler & stateHandler;
public:
    VideoPlayingState(VideoStateHandler &stateHandler);

    void play() override;
    void stop() override;
    void pause() override;


};


#endif //VALRAVEN_VIDEOPLAYINGSTATE_H
