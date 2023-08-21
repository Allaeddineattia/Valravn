//
// Created by alro on 6‏/12‏/2020.
//

#ifndef VALRAVEN_VLC_WRAPPER_H
#define VALRAVEN_VLC_WRAPPER_H

#include <vlc/vlc.h>
#include <memory>
#include <functional>
#include <media_player/Multimedia.h>
#include <core/IObeserver.h>

using namespace std;

class VLC_Wrapper {
    libvlc_instance_t * vlcInstance;
    libvlc_media_player_t  * mediaPlayer;
    libvlc_event_manager_t * mediaPlayerEventManager;
    libvlc_media_t * media;
    int x;
    void onPlayVideo();
    void onPauseVideo();
    void onStopVideo();
    IObserver * observer;

public:
    IObserver * next_observer = nullptr;
    VLC_Wrapper();
    bool media_player_locked = false;
    void playVideo(string_view path, int length);

    void onMediaEnd(IObserver * observer);
    void setFullScreen();
    void pause();
    void resume();
    void stop();
    void terminate();
    void setNextMedia();

    time_t getDurationOfMedia(string_view path);

    virtual ~VLC_Wrapper();

    int increaseVolume();

    int decreaseVolume();
};


#endif //VALRAVEN_VLC_WRAPPER_H
