//
// Created by rawaa on 25‏/12‏/2020.
//

#ifndef MYPROJECT_SCHEDULEREPO_H
#define MYPROJECT_SCHEDULEREPO_H

#include <optional>
#include <DataBase/Contracts/IRepository.h>
#include <Entity/Contract/Schedule.h>


class ScheduleRepo: public IRepository<Schedule> {
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;


public:

    template<class Dependency>
    explicit ScheduleRepo(shared_ptr<Dependency> dependency_injector);

    [[nodiscard]] const string & getTableName() const override;

    optional<unique_ptr<Schedule>> getById(unsigned int id) override;

    vector<unique_ptr<Schedule>> getAll() override;

    [[nodiscard]] void save(const Schedule& element) override;

    void deleteById(unsigned int id) override;

    virtual ~ScheduleRepo();
};

#endif //MYPROJECT_SCHEDULEREPO_H
