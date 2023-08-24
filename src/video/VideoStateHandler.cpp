//
// Created by alro on 14‏/12‏/2020.
//

#include <utility>
#include <iostream>

#include <core/DependencyInjector.h>
#include <video/playing_state/VideoStateHandler.h>



VideoPlayingState * VideoStateHandler::get_playing_state() const {
    return playing_state.get();
}

VideoPausedState * VideoStateHandler::get_paused_state() const {
    return paused_state.get();
}

VideoStoppedState * VideoStateHandler::get_stopped_state() const {
    return stopped_state.get();
}

IPlayable &VideoStateHandler::get_state() const {
    return *state;
}

void VideoStateHandler::play() {
    vlc->next_observer = static_cast<IObserver *>(this);
    state->play();
}

void VideoStateHandler::stop() {
    state->stop();
}

void VideoStateHandler::pause() {
    state->pause();
}

void VideoStateHandler::set_state(IPlayable  * state) {
    VideoStateHandler::state = state;
}


VLC_Wrapper & VideoStateHandler::get_vlc() const {
    return *vlc;
}

void VideoStateHandler::update() {
    cout << "Video path " << this->video.get_multimedia().getPath() << endl;
    this->update_function();
}

void VideoStateHandler::set_update_function(function<void()> updateFunction) {
    VideoStateHandler::update_function = std::move(updateFunction);
}




