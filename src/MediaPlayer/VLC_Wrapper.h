//
// Created by alro on 6‏/12‏/2020.
//

#ifndef MYPROJECT_VLC_WRAPPER_H
#define MYPROJECT_VLC_WRAPPER_H

#include <vlc/vlc.h>
#include <memory>
#include <Entity/Multimedia.h>

using namespace std;

class VLC_Wrapper {
    shared_ptr<libvlc_instance_t> vlcInstance;
    libvlc_media_player_t  * mediaPlayer;
    libvlc_event_manager_t * mediaPlayerEventManager;

    




};


#endif //MYPROJECT_VLC_WRAPPER_H
