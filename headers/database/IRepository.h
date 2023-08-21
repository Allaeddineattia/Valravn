//
// Created by alro on 25‏/11‏/2020.
//

#ifndef VALRAVEN_IREPOSITORY_H
#define VALRAVEN_IREPOSITORY_H
#include <vector>
#include <optional>
#include <memory>

using namespace std;

template<typename Entity>
class IRepository {
public:
    [[nodiscard]] virtual const string & getTableName() const = 0;
    virtual void save(const Entity &) = 0;
    virtual void deleteById(unsigned int id) = 0;
    virtual optional<unique_ptr<Entity>> getById(unsigned  int id) = 0;
    virtual vector<unique_ptr<Entity>> getAll() = 0;
};



#endif //VALRAVEN_IREPOSITORY_H
