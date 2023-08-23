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
        static void install_repo(shared_ptr<IRepository<Entity>> iRepository) {
            PersistentEntity::repo = iRepository;
        };

        void save() {
            assert(repo);
            repo->save(get_savable());

        };

        void remove() {
            assert(repo);
            repo->delete_by_id(get_id());
        };

        virtual const Entity & get_savable() = 0;

        [[nodiscard]] virtual unsigned int get_id() const = 0;

        [[nodiscard]] static unsigned int generate_new_id(){
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

        static optional<unique_ptr<Entity>> fetch_by_id(unsigned int id){
            assert(repo);
            return repo->get_by_id(id);
        };
        static vector<unique_ptr<Entity>> get_all(){
            assert(repo);
            return repo->get_all();
        };

        virtual ~PersistentEntity() {  };

    };
}




#endif //VALRAVEN_SAVABLE_H
