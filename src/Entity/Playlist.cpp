//
// Created by ismail on 16‏/11‏/2020.
//

#include "Entity/Playlist.h"
#include <vector>
#include <algorithm>

using namespace std;


Playlist::Playlist(int id) : id(id){}

const vector<unique_ptr<MediaDisplay>> & Playlist::getPlaylist()  {
    return playlist;
}

void Playlist::addPlayabal(unique_ptr<MediaDisplay> playabale) {
    auto vit = find(playlist.begin(), playlist.end(), playabale);
    if (vit != playlist.end())
        throw  invalid_argument("Element  already exists ");
    else
        playlist.push_back(move(playabale));
}


void Playlist::removePlayabal(unique_ptr<MediaDisplay> playabale) {
    vector<unique_ptr<MediaDisplay>>::iterator vit = find(playlist.begin(), playlist.end(),playabale);
    if (vit != playlist.end())
        playlist.erase(vit);
    else
        throw  invalid_argument("Element  NOT exists ");

}

int Playlist::getId() const {
    return id;
}

void Playlist::play() {
    for(current = 0; current < playlist.size(); current ++)
        playlist[current]->getPlayabale()->play();
}

void Playlist::pause() {
    playlist[current] -> getPlayabale()-> pause();
}

void Playlist::stop() {
    playlist[current] -> getPlayabale()-> stop();
    current = 0;
}



