//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_AUDIO_H
#define MYPROJECT_AUDIO_H
#include <stdio.h>
#include <memory>
#include "Multimedia.h"

class Audio {

private:
    int id;
    int duration ;
    unique_ptr<Multimedia> multimedia ;

public:
    [[nodiscard]]const unique_ptr<Multimedia> &getMultimedia() const;

    [[nodiscard]]int getId() const;

    [[nodiscard]]int getDuration() const;

    Audio(int id, int duration ,unique_ptr<Multimedia> multimedia);


};


#endif //MYPROJECT_AUDIO_H
