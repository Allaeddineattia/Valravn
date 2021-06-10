//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_VIDEO_H
#define MYPROJECT_VIDEO_H


#include "Multimedia.h"
#include <string>
#include <memory>
#include <Entity/Contract/VideoState/VideoStateHandler.h>
#include "IPlayable.h"
class VideoStateHandler;
using namespace std;

class Video;

class Video : public IPlayable, public Savable<Video>{
private:

    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;
    string resolution ;
    unique_ptr<VideoStateHandler> stateHandler;
public:
    virtual ~Video() = default;

    [[nodiscard]] unsigned int getId() const override;

    [[nodiscard]]int getDuration() const;

    [[nodiscard]]const Multimedia &getMultimedia() const;

    [[nodiscard]]string_view getResolution() const;

    const Video & getSavable() override{
        return *this;
    }

    void setStateHandler(unique_ptr<VideoStateHandler> stateHandler);

    void play() override ;

    void stop() override ;

    void pause() override;


    Video(int id, int duration, unique_ptr<Multimedia> multimedia, string_view resolution);


};


#endif //MYPROJECT_VIDEO_H
