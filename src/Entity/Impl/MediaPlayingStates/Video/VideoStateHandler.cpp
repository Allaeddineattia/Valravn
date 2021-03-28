//
// Created by alro on 14‏/12‏/2020.
//

#include <Shared/DependencyInjector.h>

#include <utility>
#include "Entity/Contract/VideoState/VideoStateHandler.h"



VideoPlayingState * VideoStateHandler::getPlayingState() const {
    return playingState.get();
}

VideoPausedState * VideoStateHandler::getPausedState() const {
    return pausedState.get();
}

VideoStoppedState * VideoStateHandler::getStoppedState() const {
    return stoppedState.get();
}

IPlayable &VideoStateHandler::getState() const {
    return *state;
}

void VideoStateHandler::play() {
    vlc->onPlayVideo(this);
    state->play();
}

void VideoStateHandler::stop() {
    vlc->onStopVideo(this);
    state->stop();
}

void VideoStateHandler::pause() {
    vlc->onPauseVideo(this);
    state->pause();
}

void VideoStateHandler::setState(IPlayable  * state) {
    VideoStateHandler::state = state;
}


VLC_Wrapper & VideoStateHandler::getVlc() const {
    return *vlc;
}

void VideoStateHandler::update() {
    this->updateFunction();
}

void VideoStateHandler::setUpdateFunction(function<void()> function) {
    VideoStateHandler::updateFunction = std::move(function);
}




