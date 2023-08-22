//
// Created by alro on 2‏/5‏/2021.
//

#ifndef VALRAVEN_MEDIASERVICES_H
#define VALRAVEN_MEDIASERVICES_H

class MediaServices{
private:
    unique_ptr<Video> current_vid;

public:
    unique_ptr<Playlist> playlist = make_unique<Playlist>(4);
    void play_video(unique_ptr<Video> video, shared_ptr<DependencyInjector> di){
        auto stateHandler = make_unique<VideoStateHandler>(di, *video);
        video->setStateHandler(std::move(stateHandler));
        try
        {
            video->play();
            current_vid = std::move(video);
        }
        catch (...)
        {
        }
    }





};

#endif //VALRAVEN_MEDIASERVICES_H
