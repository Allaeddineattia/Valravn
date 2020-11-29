//
// Created by alro on 21‏/11‏/2020.
//

#ifndef MYPROJECT_MEDIADISPLAY_H
#define MYPROJECT_MEDIADISPLAY_H

#include <memory>
#include <Entity/IPlayable.h>
#include <Entity/Parameter.h>
using namespace std;

class MediaDisplay {
private:
    unique_ptr<IPlayable> playable;
    unique_ptr<Parameter> parameter;

public:
    MediaDisplay(unique_ptr<IPlayable> playabale, unique_ptr<Parameter> parameter);

    IPlayable &getPlayabale() ;

    Parameter &getParameter() ;
};


#endif //MYPROJECT_MEDIADISPLAY_H
