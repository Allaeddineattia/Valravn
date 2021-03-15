//
// Created by alro on 14‏/12‏/2020.
//

#ifndef MYPROJECT_VIDEOPAUSEDSTATE_H
#define MYPROJECT_VIDEOPAUSEDSTATE_H


#include <Entity/IPlayable.h>
#include <Entity/Video.h>
#include "Entity/MediaPlayingStates/Video/VideoStateHandler.h"
class VideoStateHandler;

class VideoPausedState: public IPlayable {
    VideoStateHandler & stateHandler;

public:
    VideoPausedState(VideoStateHandler &stateHandler);

    void play() override;
    void stop() override;
    void pause() override;

};


#endif //MYPROJECT_VIDEOPAUSEDSTATE_H
