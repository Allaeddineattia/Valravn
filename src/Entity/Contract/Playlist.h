//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef MYPROJECT_PLAYLIST_H
#define MYPROJECT_PLAYLIST_H
#include "IPlayable.h"
#include <memory>
#include <vector>
#include <Entity/Contract/MediaDisplay.h>
using namespace std;


class Playlist : public IPlayable , public IObserver{
private:
    int id;
    vector<unique_ptr<MediaDisplay>> display;
    int current = 0;

public:
    Playlist(int id);
    ~Playlist() override = default;

    [[nodiscard]] int getId() const;

    [[nodiscard]] const vector<unique_ptr<MediaDisplay>> & getPlaylist();

    void addMediaDisplay(unique_ptr<MediaDisplay> _mediaDisplay);

    void removePlayable(int _position);

    void play_next ();

    void play_previous ();

    void play () override;

    void pause () override;

    void stop () override;

    void update() override;

};


#endif //MYPROJECT_PLAYLIST_H

