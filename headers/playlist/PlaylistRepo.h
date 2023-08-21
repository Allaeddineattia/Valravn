//
// Created by rawaa on 20‏/3‏/2021.
//

#ifndef VALRAVN_PLAYLISTREPO_H
#define VALRAVN_PLAYLISTREPO_H

namespace DataBase
{
    class PlaylistRepo{
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;

    };
}

#endif //VALRAVN_PLAYLISTREPO_H
