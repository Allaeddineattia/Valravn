//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef VALRAVEN_PLAYLIST_H
#define VALRAVEN_PLAYLIST_H

#include <memory>
#include <vector>

#include <media_player/IPlayable.h>
#include <media_player/MediaDisplay.h>
#include <core/IObeserver.h>
using namespace std;


class Playlist : public IPlayable , public IObserver{
private:
    int id;
    vector<unique_ptr<MediaDisplay>> display;
    unsigned long current = 0;

public:
    explicit Playlist(int id);
    ~Playlist() override = default;

    [[nodiscard]] int get_id() const;

    [[nodiscard]] const vector<unique_ptr<MediaDisplay>> & get_playlist();

    void add_media_display(unique_ptr<MediaDisplay> _mediaDisplay);

    void remove_playable(int _position);

    void play_next ();

    void play_previous ();

    void play () override;

    void pause () override;

    void stop () override;

    void update() override;

};


#endif //VALRAVEN_PLAYLIST_H

