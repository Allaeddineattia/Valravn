//
// Created by rawaa on 25‏/12‏/2020.
//

#ifndef VALRAVEN_SCHEDULEREPO_H
#define VALRAVEN_SCHEDULEREPO_H

#include <optional>
#include <database/IRepository.h>
#include <playlist/Schedule.h>

namespace DataBase
{
    class ScheduleRepo: public IRepository<Schedule> {
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
        
    public:

        template<class Dependency>
        explicit ScheduleRepo(shared_ptr<Dependency> dependency_injector);

        [[nodiscard]] const string & get_table_name() const override;

        optional<unique_ptr<Schedule>> get_by_id(unsigned int id) override;

        vector<unique_ptr<Schedule>> get_all() override;

        void save(const Schedule& element) override;

        void delete_by_id(unsigned int id) override;

        virtual ~ScheduleRepo();
    };
}


#endif //VALRAVEN_SCHEDULEREPO_H
