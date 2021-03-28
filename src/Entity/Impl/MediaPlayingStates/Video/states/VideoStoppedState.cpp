//
// Created by alro on 14‏/12‏/2020.
//

#include "Entity/Contract/VideoState/VideoStoppedState.h"
#include "iostream"

void VideoStoppedState::play() {
    cout<<"VideoStoppedState::play, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.setUpdateFunction
    ([this](){
        this->stateHandler.setState(stateHandler.getPlayingState());
    });
    stateHandler.getVlc().playVideo(stateHandler.video.getMultimedia().getPath(), stateHandler.video.getDuration());

}

void VideoStoppedState::stop() {
    cout<<"VideoStoppedState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

void VideoStoppedState::pause() {
    cout<<"VideoStoppedState::pause, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

VideoStoppedState::VideoStoppedState(VideoStateHandler &stateHandler) : stateHandler(stateHandler) {}
