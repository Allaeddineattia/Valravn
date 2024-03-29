//
// Created by alro on 14‏/12‏/2020.
//

#include <video/playing_state/VideoStoppedState.h>
#include "iostream"

void VideoStoppedState::play() {
    cout << "VideoStoppedState::play, path: " << state_handler.video.get_multimedia().getPath() << endl;
    state_handler.set_update_function
            ([this]() {
                this->state_handler.set_state(state_handler.get_playing_state());
            });
    state_handler.get_vlc().play_video(state_handler.video.get_multimedia().getPath(), state_handler.video.get_duration());

}

void VideoStoppedState::stop() {
    cout << "VideoStoppedState::stop, path: " << state_handler.video.get_multimedia().getPath() << endl;
}

void VideoStoppedState::pause() {
    cout << "VideoStoppedState::pause, path: " << state_handler.video.get_multimedia().getPath() << endl;
}

VideoStoppedState::VideoStoppedState(VideoStateHandler &stateHandler) : state_handler(stateHandler) {}
