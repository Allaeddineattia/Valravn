//
// Created by alro on 18‏/10‏/2020.
//

#include "Multimedia.h"

int Multimedia::getId() const {
    return id;
}

string_view Multimedia::getPath() const {
    return path;
}

size_t Multimedia::getSize() const {
    return size;
}

string_view Multimedia::getMimeType() const {
    return mimeType;
}

Multimedia::Multimedia(int id, string_view path, size_t size, string_view mimeType) : id(id), path(path),
                                                                                      size(size),
                                                                                      mimeType(mimeType) {}
