//
// Created by alro on 14‏/12‏/2020.
//

#include "iostream"
#include <video/playing_state/VideoPausedState.h>

void VideoPausedState::play() {
    cout<<"VideoPausedState::play, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.setUpdateFunction([this](){
        this->stateHandler.setState(this->stateHandler.getPlayingState());
    });
    stateHandler.getVlc().resume();


}

void VideoPausedState::stop() {
    cout<<"VideoPausedState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.setUpdateFunction([this](){
        this->stateHandler.setState(this->stateHandler.getStoppedState());
    });
    stateHandler.getVlc().stop();
}

void VideoPausedState::pause() {
    cout<<"VideoPausedState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

VideoPausedState::VideoPausedState(VideoStateHandler & stateHandler) : stateHandler(stateHandler) {}

