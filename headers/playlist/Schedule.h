//
// Created by alro on 21‏/11‏/2020.
//

#ifndef VALRAVEN_SCHEDULE_H
#define VALRAVEN_SCHEDULE_H

#include <ctime>
#include <memory>
#include <playlist/Playlist.h>
#include <media_player/Parameter.h>

class Schedule {
private:
    int id;
    time_t time;

    std::unique_ptr<Playlist> playlist;


public:
    Schedule(int id,time_t time, unique_ptr<Playlist> playlist);

    [[nodiscard]]int get_id() const;

    [[nodiscard]] time_t get_time() const;

    [[nodiscard]] const Playlist & get_playlist() const;
};


#endif //VALRAVEN_SCHEDULE_H
