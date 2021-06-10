//
// Created by alro on 28‏/11‏/2020.
//

#ifndef MYPROJECT_MULTIMEDIAREPO_H
#define MYPROJECT_MULTIMEDIAREPO_H
#include <string>
#include <sstream>
#include <DataBase/Contracts/DataBase.h>
#include <Entity/Contract/Multimedia.h>

using namespace std;


class MultimediaRepo: public IRepository<Multimedia> {
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;

public:
    template<class Dependency>
    explicit MultimediaRepo(Dependency dependency_injector);

    [[nodiscard]] const string & getTableName() const;

    optional<unique_ptr<Multimedia>> getById(unsigned int id) override;

    [[nodiscard]] vector<unique_ptr<Multimedia>> getAll() override;

    void save(const Multimedia& element) override;

    void deleteById(unsigned int id) override;

    virtual ~MultimediaRepo();
};


#endif //MYPROJECT_MULTIMEDIAREPO_H
