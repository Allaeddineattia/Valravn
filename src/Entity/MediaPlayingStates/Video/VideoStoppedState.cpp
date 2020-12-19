//
// Created by alro on 14‏/12‏/2020.
//

#include "VideoStoppedState.h"
#include "iostream"

void VideoStoppedState::play() {
    cout<<"VideoStoppedState::play, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
    stateHandler.setState(stateHandler.getPlayingState());

}

void VideoStoppedState::stop() {
    cout<<"VideoStoppedState::stop, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
}

void VideoStoppedState::pause() {
    cout<<"VideoStoppedState::pause, path: "<<stateHandler.video.getMultimedia()->getPath()<<endl;
}

VideoStoppedState::VideoStoppedState(VideoStateHandler &stateHandler) : stateHandler(stateHandler) {}
