//
// Created by alro on 25‏/11‏/2020.
//

#ifndef MYPROJECT_SAVABLE_H
#define MYPROJECT_SAVABLE_H
#include <vector>
#include <optional>
#include <Shared/CustomError.h>
#include <memory>
#include <cassert>
#include <DataBase/Contracts/IRepository.h>
#include <random>
using namespace std;
#define MAX_ID 1000000;
template<class Entity>
class Savable {

protected:
    static inline shared_ptr<IRepository<Entity>> repo;
public:
    static void installRepo(shared_ptr<IRepository<Entity>> iRepository) {
        Savable::repo = iRepository;
    };

    bool save() {
        assert(repo);
        try{
            return repo->save(getSavable());
        }catch (const char * str){
            throw str;
        }

    };

    bool remove() {
        assert(repo);
        return repo->delete_by_id(getId());
    };

    virtual const Entity & getSavable() = 0;

    [[nodiscard]] virtual unsigned int getId() const = 0;

    [[nodiscard]] static unsigned int createNewId(){
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        int max = MAX_ID;
        std::uniform_int_distribution<> distrib(1, max);
        unsigned int id = distrib(gen);
        auto res = repo->get_by_id(id);
        while (res.has_value() && res.value()){
            id = distrib(gen);
            res = repo->get_by_id(id);
        };
        return id;
    };

    static optional<unique_ptr<Entity>> fetchById(unsigned int id){
        assert(repo);
        return repo->get_by_id(id);
    };
    static vector<unique_ptr<Entity>> getAll(){
        assert(repo);
        return repo->get_all();
    };

    virtual ~Savable() {  };

};


#endif //MYPROJECT_SAVABLE_H
