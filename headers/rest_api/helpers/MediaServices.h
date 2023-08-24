//
// Created by alro on 2‏/5‏/2021.
//

#ifndef VALRAVEN_MEDIASERVICES_H
#define VALRAVEN_MEDIASERVICES_H

class MediaServices{
private:
    unique_ptr<Video> current_vid = nullptr;

public:
    unique_ptr<Playlist> playlist = make_unique<Playlist>(4);
    void play_video(unique_ptr<Video> video, shared_ptr<DependencyInjector> di){
        auto stateHandler = make_unique<VideoStateHandler>(di, *video);
        video->set_state_handler(std::move(stateHandler));
        try
        {
            video->play();
            current_vid = std::move(video);
        }
        catch (...)
        {
        }
    }

    [[nodiscard]] Video* get_current_vid() const {
        return current_vid.get();
    }
};

#endif //VALRAVEN_MEDIASERVICES_H
