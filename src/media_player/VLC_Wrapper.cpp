//
// Created by alro on 6‏/12‏/2020.
//

#include <unistd.h>
#include <iostream>
#include <thread>
#include <video/Video.h>
#include <media_player/VLC_Wrapper.h>

using namespace std;

typedef void (*VLC_Callback)(const libvlc_event_t *, void *);


VLC_Wrapper::VLC_Wrapper() : vlcInstance(libvlc_new(0, nullptr)),
mediaPlayer(libvlc_media_player_new(vlcInstance)) ,
mediaPlayerEventManager(libvlc_media_player_event_manager(mediaPlayer))
{
    VLC_Callback on_media_change = [](const struct libvlc_event_t *p_event, void *p_data) {
        cout << "[libvlc_event_attach] libvlc_MediaPlayerMediaChanged" << endl;
        VLC_Wrapper * data = static_cast<VLC_Wrapper *> (p_data);
        data->resume();
    };

    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerMediaChanged,
                        on_media_change, this);

    initialise_counter = 0;
    thread([&](){
        while(true){
            if(initialise_counter == 1){
                cout<<"setting media"<<endl;
                libvlc_media_player_set_media(mediaPlayer, media);
                initialise_counter=0;
            }
            if(initialise_counter == 2){
                break;
            }
        }
    }).detach();

    on_play_video();
    on_pause_video();
    on_stop_video();

}

void VLC_Wrapper::play_video(string_view path, int length) {
    media = libvlc_media_new_path(vlcInstance, path.data());
    set_next_media();
}

void VLC_Wrapper::set_next_media() {
    initialise_counter = 1;
}

void VLC_Wrapper::pause() {
    if(libvlc_media_player_can_pause(mediaPlayer)){
        libvlc_media_player_pause(mediaPlayer);
    }
}

void VLC_Wrapper::resume() {

    cout<<"VLC_Wrapper::resume"<<endl;
    libvlc_media_player_play(mediaPlayer);
}


time_t VLC_Wrapper::get_media_duration(string_view path) {
    libvlc_media_t * vMedia = libvlc_media_new_path(vlcInstance, path.data());
    libvlc_media_parse_with_options(vMedia, libvlc_media_parse_local, -1);
    time_t duration;
    VLC_Callback on_media_parsed = [](const struct libvlc_event_t *p_event, void *p_data){
        libvlc_media_t * pMedia = static_cast<libvlc_media_t *> (p_event->p_obj);
        * (time_t *) p_data = libvlc_media_get_duration(pMedia);
    };

    libvlc_event_attach(libvlc_media_event_manager(vMedia), libvlc_event_e::libvlc_MediaParsedChanged,
                        on_media_parsed, &duration);
    usleep(100000);
    return duration;

}



void VLC_Wrapper::on_play_video() {
    cout<<"on_play_video"<<endl;
    VLC_Callback on_media_playing = [](const struct libvlc_event_t *p_event, void *p_data){
        cout<<"[libvlc_event_attach] on_play_video"<<endl;
        VLC_Wrapper * vlc = static_cast<VLC_Wrapper *>(p_data) ;
        IObserver * observer = dynamic_cast<IObserver *>(vlc->next_observer);
        if(observer){
            vlc->observer = observer;
            observer->update();
        }
    };

    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPlaying,
                        on_media_playing, (void *) this);
}

void VLC_Wrapper::on_pause_video() {
    VLC_Callback on_media_pausing = [](const struct libvlc_event_t *p_event, void *p_data){
        cout<<"[libvlc_event_attach] on_pause_video"<<endl;
        VLC_Wrapper * vlc = static_cast<VLC_Wrapper *>(p_data) ;
        IObserver * observer = static_cast<IObserver *>(vlc->observer);
        if(observer)
        {
            observer->update();
        }
    };

    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPaused,
                        on_media_pausing, (void *) this);

}

void VLC_Wrapper::stop() {
    if( libvlc_media_player_is_playing(mediaPlayer))
    {
        libvlc_media_player_stop(mediaPlayer);
    }else
    {
        observer->update();
    }
}

void VLC_Wrapper::on_stop_video() {

    VLC_Callback on_media_stopped = [](const struct libvlc_event_t *p_event, void *p_data){
        cout<<"[libvlc_event_attach] on_stop_video"<<endl;
        VLC_Wrapper * vlc = static_cast<VLC_Wrapper *>(p_data) ;
        IObserver * vObserver = static_cast<IObserver *>(vlc->observer);
        if(vObserver)
        {
            vObserver->update();
        }

    };

    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerStopped,
                        on_media_stopped, (void *) this);


}

void VLC_Wrapper::on_media_end(IObserver *observer) {

    VLC_Callback on_media_reached_end = [](const struct libvlc_event_t *p_event, void *p_data){
        auto * vObserver = static_cast<IObserver *>(p_data);
        cout<<"[libvlc_MediaPlayerEndReached]"<<endl;
        vObserver->update();
        cout<<"[libvlc_MediaPlayerEndReached]"<<endl;
    };

    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerEndReached,
                        on_media_reached_end, (void *) observer);
}

void VLC_Wrapper::set_fullscreen() {
    libvlc_set_fullscreen(mediaPlayer, 1);

}

int VLC_Wrapper::increase_volume(){
    int vol = libvlc_audio_get_volume(mediaPlayer);
    int result = vol + 5;
    result = result < 100 ? result : 100;
    libvlc_audio_set_volume(mediaPlayer, result);
    return libvlc_audio_get_volume(mediaPlayer);

}

int VLC_Wrapper::decrease_volume(){
    int vol = libvlc_audio_get_volume(mediaPlayer);
    int result = vol - 5;
    result = result > 0 ? result : 0;
    libvlc_audio_set_volume(mediaPlayer, result);
    return libvlc_audio_get_volume(mediaPlayer);
}

void VLC_Wrapper::terminate() {
    initialise_counter=2;
    libvlc_media_release(media);
    libvlc_media_player_release(mediaPlayer);

}


VLC_Wrapper::~VLC_Wrapper() {
    cout<<"releasing mediaPlayer"<<endl;
    libvlc_media_player_release(mediaPlayer);
    cout<<"releasing vlcInstance"<<endl;
    libvlc_release(vlcInstance);
}











