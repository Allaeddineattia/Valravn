//
// Created by alro on 18‏/10‏/2020.
//

#ifndef MYPROJECT_MULTIMEDIA_H
#define MYPROJECT_MULTIMEDIA_H
#include <string>
#include <string_view>
#include <memory>
#include <DataBase/Contracts/IRepository.h>
#include "DataBase/Contracts/Savable.h"

using namespace std;

class Multimedia : public Savable<Multimedia>{
private:
    unsigned int id;
    string path;
    size_t size;
    string mimeType;

public:
    Multimedia(unsigned int id, string_view path, size_t size, string_view mimeType);

    [[nodiscard]] unsigned int getId() const override;

    [[nodiscard]] string_view getPath() const;

    [[nodiscard]] size_t getSize() const;

    [[nodiscard]] string_view getMimeType() const;

    const Multimedia & getSavable() override {
        return *this;
    }

    static unique_ptr<Multimedia> fetch_by_id(int);

    static vector<unique_ptr<Multimedia>> get_all();

    bool operator==(const Multimedia &rhs) const;

    virtual ~Multimedia();
};


#endif //MYPROJECT_MULTIMEDIA_H
