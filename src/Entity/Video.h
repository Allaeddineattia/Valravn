//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_VIDEO_H
#define MYPROJECT_VIDEO_H


#include "Entity/Multimedia.h"
#include <string>
#include <memory>
#include "Playabale.h"

class Video : public Playabale{
private:

    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;
    string resolution ;
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
