//
// Created by alro on 6‏/12‏/2020.
//

#include <unistd.h>
#include "VLC_Wrapper.h"
#include <iostream>
#include <thread>

using namespace std;

VLC_Wrapper::VLC_Wrapper() : vlcInstance(libvlc_new(0, nullptr)),
mediaPlayer(libvlc_media_player_new(vlcInstance)) ,
mediaPlayerEventManager(libvlc_media_player_event_manager(mediaPlayer))
{}

void VLC_Wrapper::playVideo(string_view path, int length) {
    cout<<"fer"<<endl;
    media = libvlc_media_new_path(vlcInstance,path.data());
    cout<<"fer"<<endl;
    libvlc_media_player_set_media(mediaPlayer, media);
    cout<<"fer"<<endl;
    resume();
    cout<<"fer"<<endl;
    libvlc_media_release(media);

}

void VLC_Wrapper::pause() {
    if(libvlc_media_player_can_pause(mediaPlayer)){
        libvlc_media_player_pause(mediaPlayer);
    }
}

void VLC_Wrapper::resume() {
    libvlc_media_player_play(mediaPlayer);
}


time_t VLC_Wrapper::getInformationAboutMedia(string_view path) {
    libvlc_media_t * media = libvlc_media_new_path(vlcInstance,path.data());
    libvlc_media_parse_with_options(media, libvlc_media_parse_local, -1);
    time_t duration;
    libvlc_event_attach(libvlc_media_event_manager(media),
                        libvlc_event_e::libvlc_MediaParsedChanged,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto media = static_cast<libvlc_media_t *> (p_event->p_obj);
                            * (time_t *) p_data = libvlc_media_get_duration(media);
                        }, &duration);
    usleep(100000);
    return duration;

}

VLC_Wrapper::~VLC_Wrapper() {
    cout<<"mediaPlayer"<<endl;
    libvlc_media_player_release(mediaPlayer);
    cout<<"vlcInstance"<<endl;
    libvlc_release(vlcInstance);
}

void VLC_Wrapper::onPlayVideo(IObserver * observer) {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPlaying,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto callback = (IObserver *) p_data;
                            callback->update();
                        }, (void *) observer);
}

void VLC_Wrapper::onPauseVideo(IObserver * observer) {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPaused,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto callback = (IObserver *) p_data;
                            callback->update();
                        }, (void *) observer);

}

void VLC_Wrapper::stop() {
    libvlc_media_player_stop(mediaPlayer);
}

void VLC_Wrapper::onStopVideo(IObserver *observer) {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerStopped,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto callback = (IObserver *) p_data;
                            callback->update();
                        }, (void *) observer);


}

void VLC_Wrapper::onTerminate(IObserver *observer) {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerEndReached,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto mp = (libvlc_media_player_t *) p_event->p_obj;
                            auto m = libvlc_media_player_get_media(mp);
                            cout<<"\n\nreleasing : "<<libvlc_media_get_mrl(m)<<"\n\n"<<endl;
                            auto callback = (IObserver *) p_data;
                            libvlc_media_release(m);
                            callback->update();

                        }, (void *) observer);
}

void VLC_Wrapper::setFullScreen() {
    libvlc_set_fullscreen(mediaPlayer, 1);

}

int VLC_Wrapper::increaseVolume(){
    int vol = libvlc_audio_get_volume(mediaPlayer);
    int result = vol + 5;
    result = result <100 ? result : 100;
    libvlc_audio_set_volume(mediaPlayer, result);
    return libvlc_audio_get_volume(mediaPlayer);

}

int VLC_Wrapper::decreaseVolume(){
    int vol = libvlc_audio_get_volume(mediaPlayer);
    int result = vol - 5;
    result = result > 0 ? result : 0;
    libvlc_audio_set_volume(mediaPlayer, result);
    return libvlc_audio_get_volume(mediaPlayer);
}

void VLC_Wrapper::terminate() {
    libvlc_media_release(media);
    libvlc_media_player_release(mediaPlayer);

}












