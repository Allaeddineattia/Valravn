//
// Created by alro on 14‏/12‏/2020.
//

#include "VideoPlayingState.h"
#include "iostream"

void VideoPlayingState::play() {
    cout<<"VideoPlayingState::play, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
}

void VideoPlayingState::stop() {
    cout<<"VideoPlayingState::stop, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
    stateHandler.setState(stateHandler.getStoppedState());

}

void VideoPlayingState::pause() {
    cout<<"VideoPlayingState::pause, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
    stateHandler.setState(stateHandler.getPausedState());

}

VideoPlayingState::VideoPlayingState(VideoStateHandler &stateHandler) : stateHandler(stateHandler) {}
