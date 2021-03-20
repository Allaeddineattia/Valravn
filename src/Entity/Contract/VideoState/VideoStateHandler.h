//
// Created by alro on 14‏/12‏/2020.
//

#ifndef MYPROJECT_VIDEOSTATEHANDLER_H
#define MYPROJECT_VIDEOSTATEHANDLER_H


#include <Entity/Contract/Video.h>
#include "VideoPlayingState.h"
#include "VideoPausedState.h"
#include "VideoStoppedState.h"

class VideoPlayingState;
class VideoPausedState;
class VideoStoppedState;
class Video;

class VideoStateHandler: public IPlayable {

    unique_ptr<VideoPlayingState> playingState;
    unique_ptr<VideoPausedState> pausedState;
    unique_ptr<VideoStoppedState> stoppedState;
    IPlayable * state;

public:

    Video & video;

    VideoStateHandler(Video &video);

    VideoPlayingState * getPlayingState() const;

    VideoPausedState * getPausedState() const;

    VideoStoppedState * getStoppedState() const;

    IPlayable &getState() const;

    void play() override;
    void stop() override;
    void pause() override;

    void setState(IPlayable * state);

};


#endif //MYPROJECT_VIDEOSTATEHANDLER_H
