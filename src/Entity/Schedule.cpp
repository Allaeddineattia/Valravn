//
// Created by alro on 21‏/11‏/2020.
//

#include "Schedule.h"

Schedule::Schedule(int id ,time_t time, unique_ptr<Playlist> playlist) : time(time), playlist(move(playlist)) {}

time_t Schedule::getTime() const {
    return time;
}

int Schedule::getId() const {
    return id;

}


const Playlist &Schedule::getPlaylist() const {
    return *playlist;
}

