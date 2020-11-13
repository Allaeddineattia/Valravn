//
// Created by ismail on 7‏/11‏/2020.
//
#include<string_view>
#include <cmath>
#include<stdexcept>
#include <iostream>
#include "Image.h"

int Image::getId() const {
    return id;
}

string_view Image::getResolution() const {
    return resolution;
}

const unique_ptr<Multimedia> &Image::getMultimedia() const {
    return multimedia;
}

Image::Image(int id, string_view resolution, unique_ptr<Multimedia>multimedia) :
id(id),
multimedia(move(multimedia))
{
    try{
        string resolution_data= resolution.data();
        int found=resolution_data.find(" ");
        while(found!=string::npos){
            resolution_data.erase(resolution_data.begin()+found);
            found=resolution_data.find(" ");
        }
        found=resolution_data.find(":");
        if((found==string::npos) || (found==0) || (found==resolution.size()))
        {
            throw invalid_argument("Error:Resolution shape int:int");
        }
        else {
            resolution_data.erase(resolution_data.begin()+found);
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
