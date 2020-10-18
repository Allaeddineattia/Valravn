//
// Created by alro on 18‏/10‏/2020.
//

#ifndef MYPROJECT_VIDEO_H
#define MYPROJECT_VIDEO_H
#include <Entity/Multimedia.h>

class Video {
private:
    unique_ptr<Multimedia> multimedia;


public:
    Video(unique_ptr<Multimedia> multimedia);

    [[nodiscard]] const Multimedia &getMultimedia() const;
};


#endif //MYPROJECT_VIDEO_H
