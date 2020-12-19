//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_VIDEO_H
#define MYPROJECT_VIDEO_H


#include "Entity/Multimedia.h"
#include <string>
#include <memory>
#include <Entity/MediaPlayingStates/Video/VideoStateHandler.h>
#include "IPlayable.h"
class VideoStateHandler;
class Video : public IPlayable{
private:

    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;
    string resolution ;
    unique_ptr<VideoStateHandler> stateHandler;
public:
    virtual ~Video() = default;

    [[nodiscard]]int getId() const;

    [[nodiscard]]int getDuration() const;

    [[nodiscard]]const unique_ptr<Multimedia> &getMultimedia() const;

    [[nodiscard]]string_view getResolution() const;

    void play() override ;

    void stop() override ;

    void pause() override;

    Video(int id, int duration, unique_ptr<Multimedia> multimedia, string_view resolution);


};


#endif //MYPROJECT_VIDEO_H
