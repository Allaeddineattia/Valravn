//
// Created by alro on 14‏/12‏/2020.
//
#include <core/DependencyInjector.h>
#include "gtest/gtest.h"
#include <media_player/Multimedia.h>
#include <video/Video.h>
TEST(VideoPlaying, Play){
    auto multimedia = make_unique<Multimedia>(1, "video_path", 50, "type");
    auto video = make_unique<Video>(1 , 5 , move (multimedia) ,"140:150" );
    video->stop();
    video->pause();
    video->play();
    video->pause();
    video->play();
    video->stop();
    video->play();
    video->pause();
    video->stop();


}

TEST(VideoPlaying, PlayVideo){
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di -> install_vlc_wrapper();
    auto vlc = di->get_vlc_wrapper(di);
    vlc->play_video(
            "/home/alro/Downloads/South Park/South Park Season 1/S01E01.Cartman Gets an Anal Probe/South Park.S01E01.Cartman Gets an Anal Probe.avi",
            10);
}

TEST(VideoPlaying, PlayVVideo) {
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector>();
    di->install_vlc_wrapper();
    auto vlc = di->get_vlc_wrapper(di);

    string path = "/home/alro/Downloads/All over in 10 seconds.mp4";

    time_t duration = 00;

    cout<<"duration: "<<duration<<endl;

    auto multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

    auto video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");

    auto stateHandler = make_unique<VideoStateHandler>(di, *video);
    video->set_state_handler(move(stateHandler));

    video->play();

    usleep(1000000);


}

TEST(VideoPlaying, PlayVideoPlaylist) {
    {
        shared_ptr<DependencyInjector> di = make_shared<DependencyInjector>();
        di->install_vlc_wrapper();
        auto vlc = di->get_vlc_wrapper(di);

        string path = "/home/alro/Downloads/All over in 10 seconds.mp4";

        time_t duration = 00;

        cout<<"duration: "<<duration<<endl;

        auto multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

        auto video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");

        auto stateHandler = make_unique<VideoStateHandler>(di, *video);
        video->set_state_handler(move(stateHandler));

        auto playlist = make_unique<Playlist>(4);

        auto parameter = make_unique<Parameter>(true, 50, 100, 0.5);

        playlist->add_media_display(make_unique<MediaDisplay>(move(video), move(parameter)));

        path = "/home/alro/Downloads/Pexels Videos 3436.mp4";

        multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

        video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");
        stateHandler = make_unique<VideoStateHandler>(di, *video);
        video->set_state_handler(move(stateHandler));

        parameter = make_unique<Parameter>(true, 50, 100, 0.5);

        playlist->add_media_display(make_unique<MediaDisplay>(move(video), move(parameter)));

        vlc->on_media_end(playlist.get());

        playlist->play();

        int x = 0;
        while(true){
            cout<<"give you input 1-increase 2-decrease 3 - pause 4 - resume 5-quit"<<endl;
            cin>>x;
            if (x == 1){
                cout << "volume : " << vlc->increase_volume() << endl;
            }else if (x ==2){
                cout << "volume : " << vlc->decrease_volume() << endl;
            }else if (x == 3){
                playlist->pause();
            }else if (x == 4){
                playlist->play();
            }
            else if (x == 5){
                playlist->play_next();
            }
            else if (x == 6){
                playlist->play_previous();
            }
            else if (x == 7){
                playlist->stop();
                exit(0);
            }
        }
    }
}