//
// Created by alro on 4‏/12‏/2020.
//

#ifndef MYPROJECT_IMAGEREPO_H
#define MYPROJECT_IMAGEREPO_H



#include <DataBase/Contracts/DataBase.h>
#include <DataBase/Contracts/Repos/MultimediaRepo.h>

#include <optional>
#include "Entity/Contract/Image.h"
#include <DataBase/Contracts/IRepository.h>



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

    [[nodiscard]] void save(const Image& element) override;

    void deleteById(unsigned int id) override;


    virtual ~ImageRepo();
};




#endif //MYPROJECT_IMAGEREPO_H
