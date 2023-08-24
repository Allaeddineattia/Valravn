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
    int initialise_counter;
    void on_play_video();
    void on_pause_video();
    void on_stop_video();
    IObserver * observer;

public:
    IObserver * next_observer = nullptr;
    VLC_Wrapper();
    bool media_player_locked = false;
    void play_video(string_view path, int length);

    void on_media_end(IObserver * observer);
    void set_fullscreen();
    void pause();
    void resume();
    void stop();
    void terminate();
    void set_next_media();

    time_t get_media_duration(string_view path);

    virtual ~VLC_Wrapper();

    int increase_volume();

    int decrease_volume();
};


#endif //VALRAVEN_VLC_WRAPPER_H
