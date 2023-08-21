//
// Created by alro on 14‏/12‏/2020.
//

#ifndef VALRAVEN_VIDEOPAUSEDSTATE_H
#define VALRAVEN_VIDEOPAUSEDSTATE_H


#include <media_player/IPlayable.h>
#include <video/Video.h>
#include "VideoStateHandler.h"
class VideoStateHandler;

class VideoPausedState: public IPlayable {
    VideoStateHandler & stateHandler;

public:
    VideoPausedState(VideoStateHandler &stateHandler);

    void play() override;
    void stop() override;
    void pause() override;


};


#endif //VALRAVEN_VIDEOPAUSEDSTATE_H
