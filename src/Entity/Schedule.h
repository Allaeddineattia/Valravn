//
// Created by alro on 21‏/11‏/2020.
//

#ifndef MYPROJECT_SCHEDULE_H
#define MYPROJECT_SCHEDULE_H

#include <ctime>
#include <memory>
#include <Entity/Playlist.h>
#include <Entity/Parameter.h>

class Schedule {
private:
    int id;
    time_t time;

    std::unique_ptr<Playlist> playlist;


public:
    Schedule(int id,time_t time, unique_ptr<Playlist> playlist);

    [[nodiscard]]int getId() const;

    [[nodiscard]] time_t getTime() const;

    const Playlist & getPlaylist() const;
};


#endif //MYPROJECT_SCHEDULE_H
