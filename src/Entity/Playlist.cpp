//
// Created by ismail on 16‏/11‏/2020.
//

#include "Entity/Playlist.h"
#include <vector>
#include <algorithm>

using namespace std;


Playlist::Playlist(int id) : id(id){}

const vector<unique_ptr<MediaDisplay>> & Playlist::getPlaylist()  {
    return display;
}

void Playlist::addMediaDisplay(unique_ptr<MediaDisplay> _mediadisplay) {
    display.push_back(move(_mediadisplay));
}


void Playlist::removePlayable(int _position) {
    if ((_position < display.size())&&(_position >= 0))
        display.erase(display.begin()+_position);
    else
        throw  invalid_argument("Element  NOT exists ");

}

int Playlist::getId() const {
    return id;
}

void Playlist::play() {
    for(current = 0; current < display.size(); current ++)
        display[current]->getPlayable().play();
}

void Playlist::pause() {
    display[current]->getPlayable().pause();
}

void Playlist::stop() {
    display[current]->getPlayable().stop();
    current = 0;
}

void Playlist::next () {
     current++;
}

void Playlist::previous (){
    current--;
}