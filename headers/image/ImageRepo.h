//
// Created by alro on 4‏/12‏/2020.
//

#ifndef VALRAVEN_IMAGEREPO_H
#define VALRAVEN_IMAGEREPO_H



#include "database/SQLiteWrapper.h"
#include <media_player/MultimediaRepo.h>

#include <optional>
#include <image/Image.h>
#include <database/IRepository.h>

namespace DataBase
{
    class ImageRepo: public IRepository<Image> {
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;


    public:

        template<class Dependency>
        explicit ImageRepo(shared_ptr<Dependency> dependency_injector);

        [[nodiscard]] const string & get_table_name() const override;

        optional<unique_ptr<Image>> get_by_id(unsigned int id) override;

        vector<unique_ptr<Image>> get_all() override;

        void save(const Image& element) override;

        void delete_by_id(unsigned int id) override;


        virtual ~ImageRepo();
    };
}






#endif //VALRAVEN_IMAGEREPO_H
