//
// Created by alro on 14‏/12‏/2020.
//

#ifndef VALRAVEN_VIDEOSTATEHANDLER_H
#define VALRAVEN_VIDEOSTATEHANDLER_H

#include "VideoPlayingState.h"
#include "VideoPausedState.h"
#include "VideoStoppedState.h"
#include <video/Video.h>
#include <media_player/VLC_Wrapper.h>

class VideoPlayingState;
class VideoPausedState;
class VideoStoppedState;
class Video;

class VideoStateHandler: public IPlayable, public IObserver {

    unique_ptr<VideoPlayingState> playingState;
    unique_ptr<VideoPausedState> pausedState;
    unique_ptr<VideoStoppedState> stoppedState;
    IPlayable * state;
    shared_ptr<VLC_Wrapper> vlc;
    std::function<void()> updateFunction;

public:

    Video & video;
    template<class DependencyInjector>
    VideoStateHandler(shared_ptr<DependencyInjector> dependencyInjector,Video &video) : video(video),
                                                                                        stoppedState(make_unique<VideoStoppedState>(*this)),
                                                                                        pausedState(make_unique<VideoPausedState>(*this)),
                                                                                        playingState(make_unique<VideoPlayingState>(*this)),
                                                                                        state(stoppedState.get()){
        vlc = dependencyInjector->get_vlc_wrapper(dependencyInjector);
        vlc->setFullScreen();
    };

    VideoPlayingState * getPlayingState() const;

    VideoPausedState * getPausedState() const;

    VideoStoppedState * getStoppedState() const;

    IPlayable &getState() const;

    void play() override;
    void stop() override;
    void pause() override;


    void setState(IPlayable * state);

    VLC_Wrapper & getVlc() const;

    void setUpdateFunction(function<void()> updateFunction);

    void update() override;

};


#endif //VALRAVEN_VIDEOSTATEHANDLER_H
