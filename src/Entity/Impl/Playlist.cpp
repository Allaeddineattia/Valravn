//
// Created by ismail on 16‏/11‏/2020.
//

#include "Entity/Contract/Playlist.h"
#include <vector>
#include <algorithm>
#include <iostream>

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
    cout<<"playing: "<< current<<endl;
    display[current]->getPlayable().play();
}



void Playlist::pause() {
    display[current]->getPlayable().pause();
}

void Playlist::stop() {
    display[current]->getPlayable().stop();
    current = 0;
}

void Playlist::play_next () {
    //this->display[current]->getPlayable().stop();
    ++current;
    cout<<current<< " , " <<display.size()<<endl;

    if(current<=display.size()){
        cout<<"ehi"<<endl;
        this->play();
    }


}

void Playlist::play_previous (){
    current--;
}

void Playlist::update() {
    cout<<"Hello Hello "<<endl;
    play_next();

}
