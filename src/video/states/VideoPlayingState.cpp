//
// Created by alro on 14‏/12‏/2020.
//

#include "iostream"
#include <video/playing_state/VideoPlayingState.h>

void VideoPlayingState::play() {
    cout<<"VideoPlayingState::play, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
}

void VideoPlayingState::stop() {
    cout<<"VideoPlayingState::stop, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.set_update_function([this]() {
        this->stateHandler.set_state(this->stateHandler.get_stopped_state());
    });
    stateHandler.get_vlc().stop();

}

void VideoPlayingState::pause() {

    cout<<"VideoPlayingState::pause, path: "<<stateHandler.video.getMultimedia().getPath()<<endl;
    stateHandler.set_update_function([this]() {
        cout << "never for ever";
        this->stateHandler.set_state(this->stateHandler.get_paused_state());
    });
    stateHandler.get_vlc().pause();


}

VideoPlayingState::VideoPlayingState(VideoStateHandler &stateHandler) : stateHandler(stateHandler) {}

