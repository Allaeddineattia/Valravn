//
// Created by alro on 28‏/11‏/2020.
//

#ifndef MYPROJECT_MULTIMEDIAREPO_H
#define MYPROJECT_MULTIMEDIAREPO_H
#include <string>
#include <sstream>
#include <DataBase/Contracts/DataBase.h>
#include <Entity/Multimedia.h>

using namespace std;


class MultimediaRepo: public IRepository<Multimedia> {
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;

public:
    template<class Dependency>
    explicit MultimediaRepo(Dependency dependency_injector);

    [[nodiscard]] const string & get_table_name() const;

    optional<unique_ptr<Multimedia>> get_by_id(unsigned int id) override;

    [[nodiscard]] vector<unique_ptr<Multimedia>> get_all() override;

    bool save(const Multimedia& element) override;

    bool delete_by_id(unsigned int id) override;

    unsigned int get_available_id() override;

    virtual ~MultimediaRepo();
};


#endif //MYPROJECT_MULTIMEDIAREPO_H
