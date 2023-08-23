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

    unique_ptr<VideoPlayingState> playing_state;
    unique_ptr<VideoPausedState> paused_state;
    unique_ptr<VideoStoppedState> stopped_state;
    IPlayable * state;
    shared_ptr<VLC_Wrapper> vlc;
    std::function<void()> update_function;

public:

    Video & video;
    template<class DependencyInjector>
    VideoStateHandler(shared_ptr<DependencyInjector> dependencyInjector,Video &video) : video(video),
                                                                                        stopped_state(make_unique<VideoStoppedState>(*this)),
                                                                                        paused_state(make_unique<VideoPausedState>(*this)),
                                                                                        playing_state(make_unique<VideoPlayingState>(*this)),
                                                                                        state(stopped_state.get()){
        vlc = dependencyInjector->get_vlc_wrapper(dependencyInjector);
        vlc->set_fullscreen();
    };

    VideoPlayingState * get_playing_state() const;

    VideoPausedState * get_paused_state() const;

    VideoStoppedState * get_stopped_state() const;

    IPlayable &get_state() const;

    void play() override;
    void stop() override;
    void pause() override;


    void set_state(IPlayable * state);

    VLC_Wrapper & get_vlc() const;

    void set_update_function(function<void()> updateFunction);

    void update() override;

};


#endif //VALRAVEN_VIDEOSTATEHANDLER_H
