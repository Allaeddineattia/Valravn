//
// Created by alro on 25‏/11‏/2020.
//

#ifndef VALRAVEN_IREPOSITORY_H
#define VALRAVEN_IREPOSITORY_H
#include <vector>
#include <optional>
#include <memory>

using namespace std;
namespace DataBase
{
    template<typename Entity>
    class IRepository {
    public:
        [[nodiscard]] virtual const string & get_table_name() const = 0;
        virtual void save(const Entity &) = 0;
        virtual void delete_by_id(unsigned int id) = 0;
        virtual optional<unique_ptr<Entity>> get_by_id(unsigned  int id) = 0;
        virtual vector<unique_ptr<Entity>> get_all() = 0;
    };
}




#endif //VALRAVEN_IREPOSITORY_H
