//
// Created by alro on 25‏/11‏/2020.
//

#ifndef VALRAVEN_SAVABLE_H
#define VALRAVEN_SAVABLE_H
#include <vector>
#include <optional>
#include <memory>
#include <cassert>
#include <random>

#include <database/IRepository.h>

using namespace std;

#define MAX_ID 1000000;

namespace DataBase
{

    template<typename Entity>
    class PersistentEntity {

    protected:
        static inline shared_ptr<IRepository<Entity>> repo;
    public:
        static void installRepo(shared_ptr<IRepository<Entity>> iRepository) {
            PersistentEntity::repo = iRepository;
        };

        void save() {
            assert(repo);
            repo->save(getSavable());

        };

        void remove() {
            assert(repo);
            repo->deleteById(getId());
        };

        virtual const Entity & getSavable() = 0;

        [[nodiscard]] virtual unsigned int getId() const = 0;

        [[nodiscard]] static unsigned int generateNewId(){
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
            int max = MAX_ID;
            std::uniform_int_distribution<> distrib(1, max);
            unsigned int id = distrib(gen);
            auto res = repo->getById(id);
            while (res.has_value() && res.value()){
                id = distrib(gen);
                res = repo->getById(id);
            };
            return id;
        };

        static optional<unique_ptr<Entity>> fetchById(unsigned int id){
            assert(repo);
            return repo->getById(id);
        };
        static vector<unique_ptr<Entity>> getAll(){
            assert(repo);
            return repo->getAll();
        };

        virtual ~PersistentEntity() {  };

    };
}




#endif //VALRAVEN_SAVABLE_H
