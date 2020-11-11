//
// Created by ismail on 7‏/11‏/2020.
//
#include<stdexcept>
#include <iostream>
#include <cmath>
#include "Video.h"
using namespace std;
Video::Video(int id, int duration,  unique_ptr<Multimedia> multimedia, string_view resolution) :
id(id),
duration(duration),
multimedia(move(multimedia))
{
    try{
        int found=resolution.find(":");
        if(found==string::npos){
            throw invalid_argument("Error:Resolution shape int:int");
        }
        else {
            string resolution_data= resolution.data();
            resolution_data.erase(resolution_data.begin()+found);
            found=resolution_data.find(" ");
            while(found!=string::npos){
                resolution_data.erase(resolution_data.begin()+found);
                found=resolution_data.find(" ");
            }
            unsigned long size=resolution_data.size()-1;
            int min=pow(10,size);
            resolution_data="0"+resolution_data;
            int i = stoi(resolution_data);
            if(i<=(min))
                throw invalid_argument("Error:Resolution shape int:int");
            else
               this->resolution=resolution;


        }
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
}

int Video::getId() const {
    return id;
}

int Video::getDuration() const {
    return duration;
}

const unique_ptr<Multimedia> &Video::getMultimedia() const {
    return multimedia;
}

string_view Video::getResolution() const {
    return resolution;
}

