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

    [[nodiscard]]int getId() const;

    [[nodiscard]] time_t getTime() const;

    [[nodiscard]] const Playlist & getPlaylist() const;
};


#endif //VALRAVEN_SCHEDULE_H
