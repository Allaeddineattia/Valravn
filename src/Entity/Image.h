//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_IMAGE_H
#define MYPROJECT_IMAGE_H

#include <string>
#include "Multimedia.h"

using namespace std;


class Image {
private:
    int id;
    string resolution ;
    unique_ptr<Multimedia> multimedia ;
public:
    Image(int id, const string &resolution,  unique_ptr<Multimedia> multimedia);

    int getId() const;

    const string &getResolution() const;

    const unique_ptr<Multimedia> &getMultimedia() const;

};


#endif //MYPROJECT_IMAGE_H
