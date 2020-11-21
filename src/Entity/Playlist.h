//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef MYPROJECT_PLAYLIST_H
#define MYPROJECT_PLAYLIST_H
#include "Playabale.h"
#include <memory>
#include <vector>
using namespace std;


class Playlist : public Playabale{
private:
    int id;
    vector<unique_ptr<Playabale>> playlist;
    int current;

public:
    [[nodiscard]] int getId() const;

    ~Playlist() override = default;

    [[nodiscard]] vector<unique_ptr<Playabale>> getPlaylist();
    void addPlayabal(unique_ptr<Playabale> playabale);
    void removePlayabal(unique_ptr<Playabale> playabale);

    void play () override;

    void pause () override;

    void stop () override;

    Playlist(vector<unique_ptr<Playabale>> _playlist, int id);
};


#endif //MYPROJECT_PLAYLIST_H

