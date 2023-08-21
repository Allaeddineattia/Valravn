//
// Created by rawaa on 20‏/12‏/2020.
//

#ifndef VALRAVEN_VIDEOREPO_H
#define VALRAVEN_VIDEOREPO_H

#include <database/DataBase.h>
#include <media_player/MultimediaRepo.h>
#include <optional>
#include <video/Video.h>
#include <database/IRepository.h>

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



    [[nodiscard]] void save(const Video& element) override;

    void deleteById(unsigned int id) override;

    virtual ~VideoRepo();
};


#endif //VALRAVEN_VIDEOREPO_H
