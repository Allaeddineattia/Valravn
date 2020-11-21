//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_IMAGE_H
#define MYPROJECT_IMAGE_H

#include <string>
#include "Multimedia.h"


using namespace std;


class Image : public Playabale{
private:

    int id;
    string resolution ;
    unique_ptr<Multimedia> multimedia ;
public:
    virtual ~Image() = default;

    Image(int id, std::string_view resolution, unique_ptr<Multimedia> multimedia);

    [[nodiscard]]int getId() const;

    [[nodiscard]]string_view getResolution() const;

    [[nodiscard]]const unique_ptr<Multimedia> &getMultimedia() const;

    void play () override;

    void pause () override;

    void stop () override;
};


#endif //MYPROJECT_IMAGE_H
