//
// Created by alro on 21‏/11‏/2020.
//

#include "Entity/Contract/Schedule.h"

Schedule::Schedule(time_t time, unique_ptr<Playlist> playlist) : time(time), playlist(move(playlist)) {}

time_t Schedule::getTime() const {
    return time;
}

const Playlist &Schedule::getPlaylist() const {
    return *playlist;
}

