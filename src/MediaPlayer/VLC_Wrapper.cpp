//
// Created by alro on 6‏/12‏/2020.
//

#include <unistd.h>
#include "VLC_Wrapper.h"
#include <iostream>
#include <thread>
#include <Entity/Contract/Video.h>

using namespace std;

VLC_Wrapper::VLC_Wrapper() : vlcInstance(libvlc_new(0, nullptr)),
mediaPlayer(libvlc_media_player_new(vlcInstance)) ,
mediaPlayerEventManager(libvlc_media_player_event_manager(mediaPlayer))
{
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerMediaChanged,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            cout<<"[libvlc_event_attach] libvlc_MediaPlayerMediaChanged"<<endl;
                            auto data = static_cast<VLC_Wrapper *> (p_data);
                            data->resume();
                        }, this);
    x = 0;
    thread([&](){
        while(true){
            if(x==1){
                cout<<"setting media"<<endl;
                libvlc_media_player_set_media(mediaPlayer, media);
                x=0;
            }
            if(x==2){
                break;
            }
        }
    }).detach();

    onPlayVideo();
    onPauseVideo();
    onStopVideo();

}

void VLC_Wrapper::playVideo(string_view path, int length) {
    media = libvlc_media_new_path(vlcInstance, path.data());
    setNextMedia();
}

void VLC_Wrapper::setNextMedia() {
    x = 1;
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


time_t VLC_Wrapper::getDurationOfMedia(string_view path) {
    libvlc_media_t * vMedia = libvlc_media_new_path(vlcInstance, path.data());
    libvlc_media_parse_with_options(vMedia, libvlc_media_parse_local, -1);
    time_t duration;
    libvlc_event_attach(libvlc_media_event_manager(vMedia),
                        libvlc_event_e::libvlc_MediaParsedChanged,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto pMedia = static_cast<libvlc_media_t *> (p_event->p_obj);
                            * (time_t *) p_data = libvlc_media_get_duration(pMedia);
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

void VLC_Wrapper::onPlayVideo() {
    cout<<"onPlayVideo"<<endl;
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPlaying,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            cout<<"[libvlc_event_attach] onPlayVideo"<<endl;
                            auto vlc = static_cast<VLC_Wrapper *>(p_data) ;
                            auto observer = dynamic_cast<IObserver *>(vlc->next_observer);
                            if(observer){
                                vlc->observer = observer;
                                observer->update();
                            }
                        }, (void *) this);
}

void VLC_Wrapper::onPauseVideo() {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerPaused,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            cout<<"[libvlc_event_attach] onPauseVideo"<<endl;
                            auto vlc = static_cast<VLC_Wrapper *>(p_data) ;
                            auto observer = static_cast<IObserver *>(vlc->observer);
                            observer->update();
                        }, (void *) this);

}

void VLC_Wrapper::stop() {
    if( libvlc_media_player_is_playing(mediaPlayer)) {
        libvlc_media_player_stop(mediaPlayer);
    }else{
        observer->update();
    }
}

void VLC_Wrapper::onStopVideo() {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerStopped,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            cout<<"[libvlc_event_attach] onStopVideo"<<endl;
                            auto vlc = static_cast<VLC_Wrapper *>(p_data) ;
                            auto vObserver = static_cast<IObserver *>(vlc->observer);
                            vObserver->update();
                        }, (void *) this);


}

void VLC_Wrapper::onMediaEnd(IObserver *vObserver) {
    libvlc_event_attach(mediaPlayerEventManager, libvlc_event_e::libvlc_MediaPlayerEndReached,
                        [](const struct libvlc_event_t *p_event, void *p_data){
                            auto * vObserver = static_cast<IObserver *>(p_data);
                            cout<<"[libvlc_MediaPlayerEndReached]"<<endl;
                            vObserver->update();
                            cout<<"[libvlc_MediaPlayerEndReached]"<<endl;
                        }, (void *) vObserver);
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
    x=2;
    libvlc_media_release(media);
    libvlc_media_player_release(mediaPlayer);

}












