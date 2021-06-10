//
// Created by alro on 16‏/4‏/2021.
//

#include "gtest/gtest.h"
#include <vlc/vlc.h>
#include "iostream"

using namespace std;
TEST(MediaParsing, Play){
    auto vlc = libvlc_new(0, nullptr);

    libvlc_media_t * vMedia = libvlc_media_new_path(vlc, "/home/alro/Dorra's Footprint/ff.mp3");

    libvlc_media_parse_with_options(vMedia, libvlc_media_parse_local, -1);
    sleep(1);
    switch (libvlc_media_get_type(vMedia)) {
        case libvlc_media_type_file:
            cout<<"type: file"<<endl;
            break;
        default:
            cout<<"type: heh"<<endl;
            break;
    }

    auto res = libvlc_media_get_meta(vMedia, libvlc_meta_Title );

    cout<<"end"<<endl;
}