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
    vector<unique_ptr<MediaDisplay>> display;
    int current;

public:
    Playlist(int id);
    ~Playlist() override = default;

    [[nodiscard]] int getId() const;
    [[nodiscard]] const vector<unique_ptr<MediaDisplay>> & getPlaylist();
    void addMediaDisplay(unique_ptr<MediaDisplay> _mediadisplay);
    void removePlayabal(int _position);
    void next ();
    void previous ();

    void play () override;

    void pause () override;

    void stop () override;

};


#endif //MYPROJECT_PLAYLIST_H

