//
// Created by alro on 14‏/12‏/2020.
//

#include "iostream"
#include <video/playing_state/VideoPausedState.h>

void VideoPausedState::play() {
    cout<<"VideoPausedState::play, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.set_update_function([this]() {
        this->stateHandler.set_state(this->stateHandler.get_playing_state());
    });
    stateHandler.get_vlc().resume();


}

void VideoPausedState::stop() {
    cout<<"VideoPausedState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.set_update_function([this]() {
        this->stateHandler.set_state(this->stateHandler.get_stopped_state());
    });
    stateHandler.get_vlc().stop();
}

void VideoPausedState::pause() {
    cout<<"VideoPausedState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

VideoPausedState::VideoPausedState(VideoStateHandler & stateHandler) : stateHandler(stateHandler) {}

