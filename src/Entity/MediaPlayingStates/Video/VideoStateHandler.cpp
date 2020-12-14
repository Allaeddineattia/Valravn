//
// Created by alro on 14‏/12‏/2020.
//

#include "VideoStateHandler.h"

VideoStateHandler::VideoStateHandler(Video &video) :
        video(video),
        stoppedState(make_unique<VideoStoppedState>(*this)),
        pausedState(make_unique<VideoPausedState>(*this)),
        playingState(make_unique<VideoPlayingState>(*this)),
        state(stoppedState.get()) {}

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

