//
// Created by alro on 25‏/11‏/2020.
//

#ifndef MYPROJECT_SAVABLE_H
#define MYPROJECT_SAVABLE_H
#include <vector>
#include <optional>
#include <Shared/CustomError.h>
#include <memory>
#include <DataBase/Contracts/IRepository.h>
using namespace std;

template<class Entity>
class Savable {

protected:
    static inline shared_ptr<IRepository<Entity>> repo;
public:
    static void installRepo(shared_ptr<IRepository<Entity>> iRepository) {
        Savable::repo = iRepository;
    };

    bool save() {
        return repo->save(getSavable());
    };

    bool remove() {
        return repo->delete_by_id(getId());
    };

    virtual const Entity & getSavable() = 0;

    [[nodiscard]] virtual unsigned int getId() const = 0;

    static optional<unique_ptr<Entity>> fetchById(unsigned int id){
        return repo->get_by_id(id);
    };
    static vector<unique_ptr<Entity>> getAll(){
        return repo->get_all();
    };

    virtual ~Savable() {  };

};



#endif //MYPROJECT_SAVABLE_H
