//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef MYPROJECT_PLAYLIST_H
#define MYPROJECT_PLAYLIST_H
#include "Playabale.h"
#include <memory>
#include <vector>
#include <Entity/MediaDisplay.h>
using namespace std;


class Playlist : public Playabale{
private:
    int id;
    vector<unique_ptr<MediaDisplay>> playlist;
    int current;

public:
    Playlist(int id);

    [[nodiscard]] int getId() const;

    ~Playlist() override = default;

    [[nodiscard]] const vector<unique_ptr<MediaDisplay>> & getPlaylist();
    void addPlayabal(unique_ptr<MediaDisplay> playabale);
    void removePlayabal(unique_ptr<MediaDisplay> playabale);

    void play () override;

    void pause () override;

    void stop () override;


};


#endif //MYPROJECT_PLAYLIST_H

