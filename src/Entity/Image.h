//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef MYPROJECT_IMAGE_H
#define MYPROJECT_IMAGE_H

#include <string>
#include "Multimedia.h"
#include "IPlayable.h"
#include <DataBase/Contracts/IRepository.h>
using namespace std;


class Image : public IPlayable, IRepository<Image>{
private:
    int id;
    string resolution;
    unique_ptr<Multimedia> multimedia;
public:
    virtual ~Image() = default;

    Image(int id, std::string_view resolution, unique_ptr<Multimedia> multimedia);

    [[nodiscard]]int getId() const;

    [[nodiscard]]string_view getResolution() const;

    [[nodiscard]]const Multimedia &getMultimedia() const;

    void play () override;

    void pause () override;

    void stop () override;

    bool save() override;

    bool remove() override;

    static unique_ptr<Image> fetch_by_id(int T);

    static vector<unique_ptr<Image>> get_all();

    bool operator==(const Image &rhs) const;
};


#endif //MYPROJECT_IMAGE_H
