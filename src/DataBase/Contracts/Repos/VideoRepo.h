//
// Created by rawaa on 20‏/12‏/2020.
//

#ifndef MYPROJECT_VIDEOREPO_H
#define MYPROJECT_VIDEOREPO_H

#include <DataBase/Contracts/DataBase.h>
#include <DataBase/Contracts/Repos/MultimediaRepo.h>
#include <optional>
#include "../../../Entity/Video.h"
#include <DataBase/Contracts/IRepository.h>

class VideoRepo: public IRepository<Video> {
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;


public:

    template<class Dependency>
    explicit VideoRepo(shared_ptr<Dependency> dependency_injector);

    [[nodiscard]] const string & getTableName() const override;

    optional<unique_ptr<Video>> getById(unsigned int id) override;

    vector<unique_ptr<Video>> getAll() override;

    [[nodiscard]] bool save(const Video& element) override;

    bool deleteById(unsigned int id) override;

    virtual ~VideoRepo();
};
};

#endif //MYPROJECT_VIDEOREPO_H
