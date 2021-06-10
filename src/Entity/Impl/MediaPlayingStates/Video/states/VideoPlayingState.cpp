//
// Created by alro on 14‏/12‏/2020.
//

#include "Entity/Contract/VideoState/VideoPlayingState.h"
#include "iostream"

void VideoPlayingState::play() {
    cout<<"VideoPlayingState::play, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

void VideoPlayingState::stop() {
    cout<<"VideoPlayingState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.setUpdateFunction([this](){
        this->stateHandler.setState(this->stateHandler.getStoppedState());
    });
    stateHandler.getVlc().stop();

}

void VideoPlayingState::pause() {

    cout<<"VideoPlayingState::pause, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.setUpdateFunction([this](){
        cout<<"never for ever";
        this->stateHandler.setState(this->stateHandler.getPausedState());
    });
    stateHandler.getVlc().pause();


}

VideoPlayingState::VideoPlayingState(VideoStateHandler &stateHandler) : stateHandler(stateHandler) {}

