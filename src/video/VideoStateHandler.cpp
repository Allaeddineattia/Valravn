//
// Created by alro on 14‏/12‏/2020.
//

#include <utility>
#include <iostream>

#include <core/DependencyInjector.h>
#include <video/playing_state/VideoStateHandler.h>



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
    vlc->next_observer = static_cast<IObserver *>(this);
    state->play();
}

void VideoStateHandler::stop() {
    state->stop();
}

void VideoStateHandler::pause() {
    state->pause();
}

void VideoStateHandler::setState(IPlayable  * state) {
    VideoStateHandler::state = state;
}


VLC_Wrapper & VideoStateHandler::getVlc() const {
    return *vlc;
}

void VideoStateHandler::update() {
    cout<<"Video path "<< this->video.getMultimedia().getPath()<<endl;
    this->updateFunction();
}

void VideoStateHandler::setUpdateFunction(function<void()> function) {
    VideoStateHandler::updateFunction = std::move(function);
}




