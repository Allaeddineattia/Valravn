//
// Created by alro on 14‏/12‏/2020.
//
#include <Shared/DependencyInjector.h>
#include "gtest/gtest.h"
#include "Entity/Contract/Multimedia.h"
#include "Entity/Contract/Video.h"
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
    vlc->playVideo(
            "/home/alro/Downloads/South Park/South Park Season 1/S01E01.Cartman Gets an Anal Probe/South Park.S01E01.Cartman Gets an Anal Probe.avi",
            10);
}

TEST(VideoPlaying, PlayVVideo) {
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector>();
    di->install_vlc_wrapper();
    auto vlc = di->get_vlc_wrapper(di);

    string path = "/home/alro/Downloads/All over in 10 seconds.mp4";

    time_t duration = vlc->getInformationAboutMedia(path);

    cout<<"duration: "<<duration<<endl;

    auto multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

    auto video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");

    auto stateHandler = make_unique<VideoStateHandler>(di, *video);
    video->setStateHandler(move(stateHandler));

    video->play();

    usleep(1000000);

    int x = 0;
    while(x != 5){
        cout<<"give you input 1-increase 2-decrease 3 - pause 4 - resume 5-quit"<<endl;
        cin>>x;
        if (x == 1){
            cout << "volume : " << vlc->increaseVolume()<< endl;
        }else if (x ==2){
            cout << "volume : " << vlc->decreaseVolume()<< endl;
        }else if (x == 3){
            video->pause();
        }else if (x == 4){
            video->play();
        }
        else if (x == 5){
            video->stop();
            exit(0);
        }
    }


}

TEST(VideoPlaying, PlayVideoPlaylist) {
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector>();
    di->install_vlc_wrapper();
    auto vlc = di->get_vlc_wrapper(di);

    string path = "/home/alro/Downloads/All over in 10 seconds.mp4";

    time_t duration = vlc->getInformationAboutMedia(path);

    cout<<"duration: "<<duration<<endl;

    auto multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

    auto video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");

    auto stateHandler = make_unique<VideoStateHandler>(di, *video);
    video->setStateHandler(move(stateHandler));

    auto playlist = make_unique<Playlist>(4);

    auto parameter = make_unique<Parameter>(true, 50, 100, 0.5);

    playlist->addMediaDisplay(make_unique<MediaDisplay>(move(video), move(parameter)));

    multimedia = make_unique<Multimedia>(2, path, 2000, "image/jpeg");

    video = make_unique<Video>(2, duration, move(multimedia), "1920:1080");
    stateHandler = make_unique<VideoStateHandler>(di, *video);
    video->setStateHandler(move(stateHandler));

    parameter = make_unique<Parameter>(true, 50, 100, 0.5);

    playlist->addMediaDisplay(make_unique<MediaDisplay>(move(video), move(parameter)));

    vlc->onTerminate(playlist.get());

    playlist->play();


    while(true);




}