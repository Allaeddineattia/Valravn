//
// Created by ismail on 16‏/11‏/2020.
//

#include "Entity/Contract/Playlist.h"
#include <vector>
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
}

void Playlist::play_next () {
    display[current]->getPlayable().stop();
    if(current + 1 < display.size()){
        ++current;
        cout<<current<< " , " <<display.size()<<endl;
        cout<<"Playlist::play_next"<<endl;
        this->play();
    }else{
        cout<<"Playlist reached end"<<endl;
        current = 0;
        cout<<"Playlist::play_next"<<endl;
        this->play();
    }


}

void Playlist::play_previous (){
    display[current]->getPlayable().stop();
    cout<<current - 1<<endl;
    if((((long)current) - 1) >= 0){
        --current;
        cout<<current<< " , " <<display.size()<<endl;
        cout<<"Playlist::play_next"<<endl;
        this->play();
    }else{
        cout<<"Playlist reached end"<<endl;
        current = display.size() - 1;
        cout<<"current: "<<current<<endl;
        this->play();
    }
}

void Playlist::update() {
    cout<<"Hello Hello "<<endl;
    display[current]->getPlayable().stop();
    if(current + 1 < display.size()){
        ++current;
        cout<<current<< " , " <<display.size()<<endl;
        cout<<"Playlist::play_next"<<endl;
        this->play();
    }else{
        cout<<"Playlist reached end"<<endl;
        current = 0;
        cout<<"Playlist::play_next"<<endl;
        this->play();
    }

}
