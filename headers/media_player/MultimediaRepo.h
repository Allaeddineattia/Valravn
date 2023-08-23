//
// Created by alro on 28‏/11‏/2020.
//

#ifndef VALRAVEN_MULTIMEDIAREPO_H
#define VALRAVEN_MULTIMEDIAREPO_H
#include <string>
#include <sstream>
#include "database/SQLiteWrapper.h"
#include <media_player/Multimedia.h>

using namespace std;

namespace DataBase
{

    class MultimediaRepo: public IRepository<Multimedia> {
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;

    public:
        template<class Dependency>
        explicit MultimediaRepo(Dependency dependency_injector);

        [[nodiscard]] const string & get_table_name() const override;

        optional<unique_ptr<Multimedia>> get_by_id(unsigned int id) override;

        [[nodiscard]] vector<unique_ptr<Multimedia>> get_all() override;

        void save(const Multimedia& element) override;

        void delete_by_id(unsigned int id) override;

        virtual ~MultimediaRepo();
    };
}

#endif //VALRAVEN_MULTIMEDIAREPO_H
