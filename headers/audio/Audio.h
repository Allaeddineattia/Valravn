//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef VALRAVEN_AUDIO_H
#define VALRAVEN_AUDIO_H
#include <memory>
#include <media_player/Multimedia.h>
#include <media_player/IPlayable.h>

class Audio : public IPlayable{

private:
    int id;
    int duration;
    unique_ptr<Multimedia> multimedia;
public:
    virtual ~Audio() = default;

    [[nodiscard]]const unique_ptr<Multimedia> &getMultimedia() const;

    [[nodiscard]]int getId() const;

    [[nodiscard]]int getDuration() const;

    void play() override;
    void stop() override;
    void pause() override;

    Audio(int id, int duration ,unique_ptr<Multimedia> multimedia);


};


#endif //VALRAVEN_AUDIO_H
