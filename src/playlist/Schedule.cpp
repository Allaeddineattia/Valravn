//
// Created by alro on 21‏/11‏/2020.
//

#include <playlist/Schedule.h>

Schedule::Schedule(int id ,time_t time, unique_ptr<Playlist> playlist) : time(time), playlist(move(playlist)) {}

time_t Schedule::get_time() const {
    return time;
}

int Schedule::get_id() const {
    return id;

}


const Playlist &Schedule::get_playlist() const {
    return *playlist;
}

