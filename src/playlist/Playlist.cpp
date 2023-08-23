//
// Created by ismail on 16‏/11‏/2020.
//

#include <playlist/Playlist.h>
#include <vector>
#include <iostream>

using namespace std;


Playlist::Playlist(int id) : id(id){}

const vector<unique_ptr<MediaDisplay>> & Playlist::get_playlist()  {
    return display;
}

void Playlist::add_media_display(unique_ptr<MediaDisplay> _mediaDisplay) {
    display.push_back(move(_mediaDisplay));
}


void Playlist::remove_playable(int _position) {
    if ((_position < display.size())&&(_position >= 0))
        display.erase(display.begin()+_position);
    else
        throw  invalid_argument("Element  NOT exists ");

}

int Playlist::get_id() const {
    return id;
}

void Playlist::play() {
    cout<<"playing: "<< current<<endl;
    display[current]->get_playable().play();
}



void Playlist::pause() {
    display[current]->get_playable().pause();
}

void Playlist::stop() {
    display[current]->get_playable().stop();
}

void Playlist::play_next () {
    display[current]->get_playable().stop();
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
    display[current]->get_playable().stop();
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
    display[current]->get_playable().stop();
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
