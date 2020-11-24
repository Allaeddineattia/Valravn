//
// Created by alro on 18‏/10‏/2020.
//

#ifndef MYPROJECT_MULTIMEDIA_H
#define MYPROJECT_MULTIMEDIA_H
#include <string>
#include <string_view>
#include <memory>


using namespace std;

class Multimedia {
private:
    int id;
    string path;
    size_t size;
    string mimeType;

public:
    Multimedia(int id, string_view path, size_t size, string_view mimeType);

    [[nodiscard]] int getId() const;

    [[nodiscard]] string_view getPath() const;

    [[nodiscard]] size_t getSize() const;

    [[nodiscard]] string_view getMimeType() const;

};


#endif //MYPROJECT_MULTIMEDIA_H
