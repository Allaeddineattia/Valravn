//
// Created by alro on 18‏/10‏/2020.
//

#include "Entity/Contract/Multimedia.h"

unsigned int Multimedia::getId() const {
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

Multimedia::Multimedia(unsigned int id, string_view path, size_t size, string_view mimeType) : id(id), path(path),
                                                                                      size(size),
                                                                                      mimeType(mimeType) {}

unique_ptr<Multimedia> Multimedia::fetch_by_id(int T) {
    return unique_ptr<Multimedia>();
}

vector<unique_ptr<Multimedia>> Multimedia::get_all() {
    return vector<unique_ptr<Multimedia>>();
}

bool Multimedia::operator==(const Multimedia &rhs) const {
    return id == rhs.id &&
           path == rhs.path &&
           mimeType == rhs.mimeType &&
           size == rhs.size;
}

Multimedia::~Multimedia() {

}

