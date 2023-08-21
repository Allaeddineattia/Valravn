//
// Created by ismail on 16‏/11‏/2020.
//

#ifndef VALRAVEN_IPLAYABLE_H
#define VALRAVEN_IPLAYABLE_H


class IPlayable {
public:

    virtual ~IPlayable() {
    }
    virtual void play() =0;
    virtual void stop() =0;
    virtual void pause() =0;

};


#endif //VALRAVEN_IPLAYABLE_H
