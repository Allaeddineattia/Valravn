//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef VALRAVEN_VIDEO_H
#define VALRAVEN_VIDEO_H



#include <string>
#include <memory>

#include <media_player/Multimedia.h>
#include <video/playing_state/VideoStateHandler.h>
#include <media_player/IPlayable.h>

class VideoStateHandler;
using namespace std;

class Video;

class Video : public IPlayable, public DataBase::PersistentEntity<Video>{
private:

    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;
    string resolution ;
    unique_ptr<VideoStateHandler> state_handler;
public:
    virtual ~Video() = default;

    [[nodiscard]] unsigned int get_id() const override;

    [[nodiscard]]int get_duration() const;

    [[nodiscard]]const Multimedia &get_multimedia() const;

    [[nodiscard]]string_view get_resolution() const;

    const Video & get_savable() override{
        return *this;
    }

    void set_state_handler(unique_ptr<VideoStateHandler> stateHandler);

    void play() override;

    void stop() override;

    void pause() override;

    Video(int id, int duration, unique_ptr<Multimedia> multimedia, string_view resolution);


};


#endif //VALRAVEN_VIDEO_H
