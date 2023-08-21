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

        [[nodiscard]] const string & getTableName() const override;

        optional<unique_ptr<Image>> getById(unsigned int id) override;

        vector<unique_ptr<Image>> getAll() override;

        void save(const Image& element) override;

        void deleteById(unsigned int id) override;


        virtual ~ImageRepo();
    };
}






#endif //VALRAVEN_IMAGEREPO_H
