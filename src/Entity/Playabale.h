//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef MYPROJECT_PLAYABALE_H
#define MYPROJECT_PLAYABALE_H


class Playabale {
public:
    virtual ~Playabale() {

    }

    virtual void play() =0 ;
    virtual void stop() =0;
    virtual void pause() =0;


};


#endif //MYPROJECT_PLAYABALE_H
