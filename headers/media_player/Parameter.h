//
// Created by alro on 21‏/11‏/2020.
//

#ifndef VALRAVEN_PARAMETER_H
#define VALRAVEN_PARAMETER_H


class Parameter {
private:
    bool fullscreen;
    int volume;
    int timeout;
    float speed;

public:
    Parameter(bool fullscreen, int volume, int timeout, float speed);

    [[nodiscard]] bool is_fullscreen() const;

    [[nodiscard]] int get_volume() const;

    [[nodiscard]] int get_timeout() const;

    [[nodiscard]] float get_speed() const;
};


#endif //VALRAVEN_PARAMETER_H
