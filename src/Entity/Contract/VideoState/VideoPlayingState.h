//
// Created by alro on 14‏/12‏/2020.
//

#ifndef MYPROJECT_VIDEOPLAYINGSTATE_H
#define MYPROJECT_VIDEOPLAYINGSTATE_H


#include <Entity/Contract/IPlayable.h>
#include <Entity/Contract/Video.h>
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


#endif //MYPROJECT_VIDEOPLAYINGSTATE_H
