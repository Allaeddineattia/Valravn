//
// Created by alro on 6‏/12‏/2020.
//

#ifndef MYPROJECT_VLC_WRAPPER_H
#define MYPROJECT_VLC_WRAPPER_H

#include <vlc/vlc.h>
#include <memory>
#include <Entity/Contract/Multimedia.h>
#include <functional>
#include "IObeserver.h"

using namespace std;

class VLC_Wrapper {
    libvlc_instance_t * vlcInstance;
    libvlc_media_player_t  * mediaPlayer;
    libvlc_event_manager_t * mediaPlayerEventManager;
    libvlc_media_t * media;

public:
    VLC_Wrapper();
    void playVideo(string_view path, int length);
    void onPlayVideo(IObserver * observer);
    void onPauseVideo(IObserver * observer);
    void onStopVideo(IObserver * observer);
    void onTerminate(IObserver * observer);
    void setFullScreen();
    void pause();
    void resume();
    void stop();
    void terminate();


    time_t getInformationAboutMedia(string_view path);

    virtual ~VLC_Wrapper();

    int increaseVolume();

    int decreaseVolume();
};


#endif //MYPROJECT_VLC_WRAPPER_H
