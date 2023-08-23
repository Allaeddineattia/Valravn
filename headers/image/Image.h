//
// Created by ismail on 7‏/11‏/2020.
//

#ifndef VALRAVEN_IMAGE_H
#define VALRAVEN_IMAGE_H

#include <string>
#include <optional>
#include <media_player/Multimedia.h>
#include <media_player/IPlayable.h>
#include <database/PersistentEntity.h>


using namespace std;

class Image;

    class Image : public IPlayable, public DataBase::PersistentEntity<Image>{
    private:
        unsigned int id;
        string resolution;
        unique_ptr<Multimedia> multimedia;

        int state = 0;

    public:
        ~Image() override = default;

        Image(int id, std::string_view resolution, unique_ptr<Multimedia> multimedia);

        [[nodiscard]] unsigned int get_id() const override;

        [[nodiscard]]string_view get_resolution() const;

        [[nodiscard]]const Multimedia &get_multimedia() const;

        const Image & get_savable() override{
            return *this;
        }

        void play () override;

        void pause () override;

        void stop () override;



        bool operator==(const Image &rhs) const;


    };




#endif //VALRAVEN_IMAGE_H
