//
// Created by ismail on 16‏/11‏/2020.
//

#include "Entity/Playlist.h"
#include <vector>
#include <algorithm>

using namespace std;


Playlist::Playlist(vector<unique_ptr<Playabale>> _playlist, int id) : playlist(move(_playlist)) {}

 vector<unique_ptr<Playabale>> Playlist::getPlaylist()  {
    return move(playlist);
}

void Playlist::addPlayabal(unique_ptr<Playabale> playabale) {
    vector<unique_ptr<Playabale>>::iterator Vit = find(playlist.begin(), playlist.end(),playabale);
    if (Vit != playlist.end())
        throw  invalid_argument("Element  already exists ");
    else
        playlist.push_back(move(playabale));
}


void Playlist::removePlayabal(unique_ptr<Playabale> playabale) {
    vector<unique_ptr<Playabale>>::iterator Vit = find(playlist.begin(), playlist.end(),playabale);
    if (Vit != playlist.end())
        playlist.erase(Vit);
    else
        throw  invalid_argument("Element  NOT exists ");

}

int Playlist::getId() const {
    return id;
}

void Playlist::play() {
    for(current = 0; current < playlist.size(); current ++)
        playlist[current]->play();
}

void Playlist::pause() {
    playlist[current] -> pause();
}

void Playlist::stop() {
    playlist[current] -> stop();
    current = 0;
}

