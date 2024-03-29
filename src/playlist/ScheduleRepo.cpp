//
// Created by rawaa on 25‏/12‏/2020.
//
#include <playlist/ScheduleRepo.h>

#include "database/SQLiteWrapper.h"
#include <playlist/Playlist.h>
#include <image/ImageRepo.h>
#include <core/DependencyInjector.h>
#include <playlist/Schedule.h>
#include <core/Tools.h>

using namespace DataBase;

class ScheduleRepo::Impl{

private:
    shared_ptr<SQLiteWrapper >  dataBase = nullptr;
    shared_ptr<IRepository<Playlist>> playlistRepo = nullptr;
    string tableName =  "Schedule";

    string get_create_table_sql() {
        return "CREATE TABLE " + tableName + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "PLAYLIST_ID INT NOT NULL,"\
                "TIME TIME NOT NULL,"\
                "FOREIGN KEY(PLAYLIST_ID) REFERENCES " + playlistRepo->get_table_name() + "(ID)"\
                ");";
    }

    [[nodiscard]] static string_map get_string_map(const Schedule& schedule) {
        string_map map;
        map.insert(string_pair("ID", to_string(schedule.get_id())));
        map.insert(string_pair("PLAYLIST_ID", to_string(schedule.get_playlist().get_id())));
        map.insert(string_pair("TIME" , SQLHelpers::to_sql_date_time(schedule.get_time())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Schedule& old_element, const   Schedule& new_element) {
        string_map map;

        if(new_element.get_playlist().get_id() != old_element.get_playlist().get_id())
            map.insert(string_pair("PLAYLIST_ID", to_string(new_element.get_playlist().get_id())));


        return map;
    }

    [[nodiscard]] unique_ptr<Schedule> get_entity_from_map(const string_map &map) {
        int  id = stoi(map.find("ID")->second);
        time_t timeS =dataBase->string_to_time_t(map.find("TIME")->second) ;
        auto Playlist = playlistRepo->get_by_id(stoi(map.find("PLAYLIST_ID")->second)).value();
        return make_unique<Schedule>(id, timeS, std::move(Playlist));
    }

    void create_element(const Schedule& element) const {
        dataBase->begin_transaction();
        try {
            playlistRepo->save(element.get_playlist());
            string_map map = get_string_map(element);
            dataBase->insert_into_table(tableName, map);
        }catch (const std::exception& ex){
            dataBase->abort_transaction();
            throw ;
        }
        dataBase->end_transaction();

    }

    void update_element(const Schedule& old_element, const Schedule& new_element) const {
        string_map map = get_update_string_map(old_element, new_element);
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.get_id()));
            dataBase->update_into_table(tableName, id, map);
        }
        playlistRepo->save(new_element.get_playlist());
    }



public:

    template<class Dependency>
    explicit Impl(shared_ptr<Dependency> dependency_injector){
        dataBase = dependency_injector->get_data_base(dependency_injector);
        playlistRepo = dependency_injector->get_playlist_repo(dependency_injector);
        dataBase->add_table_creation_sql(get_create_table_sql());
    }


    [[nodiscard]] const string & get_table_name() {
        return tableName;
    };

    optional<unique_ptr<Schedule>> get_by_id(unsigned int id) {
        auto schedule_map = dataBase->get_by_id(tableName, to_string(id));
        if(!schedule_map.empty())
            return get_entity_from_map(schedule_map);
        return std::nullopt;
    };

    vector<unique_ptr<Schedule>> get_all() {
        vector<string_map> vector_res = dataBase->get_all(tableName);
        vector<unique_ptr<Schedule>> schedules;
        for(auto &schedule_map: vector_res) {
            auto Playlist = playlistRepo->get_by_id(stoi(schedule_map.find("MULTIMEDIA_ID")->second));
            if(Playlist) schedules.push_back(get_entity_from_map(schedule_map));
        }
        return  schedules;
    };

    [[nodiscard]] void save(const Schedule& element) {

        auto exist = get_by_id(element.get_id());
        if(exist.has_value()){
            auto schedule = move(exist.value());
            if(schedule){
                return update_element(*schedule, element);
            }

        }
        create_element(element);
    };

    void delete_by_id(unsigned int id) {
        string_pair feature_selection("ID", to_string(id));
        auto schedule = get_by_id(id);
        if(!schedule.has_value()){
            throw "No Element found with id ";
        }
        dataBase->begin_transaction();
        try{
            dataBase->delete_by_feature(tableName, feature_selection);
            playlistRepo->delete_by_id(schedule.value()->get_playlist().get_id());
        }catch (const std::exception& ex){
            dataBase->abort_transaction();
            throw ;
        }

        dataBase->end_transaction();
    }
    unsigned int get_available_id() {
        unsigned int id = Tools::generate_random_value();
        while(get_by_id(id).has_value())
            id = Tools::generate_random_value();
        return id;
    }


};

void save(const Schedule &element);

const string &ScheduleRepo::get_table_name()  const {
    return mImpl->get_table_name();
}

optional<unique_ptr<Schedule>> ScheduleRepo::get_by_id(unsigned int id) {
    return mImpl->get_by_id(id);
}

vector<unique_ptr<Schedule>> ScheduleRepo::get_all() {
    return mImpl->get_all();
}

void ScheduleRepo::save(const Schedule &element) {
    mImpl->save(element);
}

void ScheduleRepo::delete_by_id(unsigned int id) {
    return mImpl->delete_by_id(id);
}

template<class Dependency>
ScheduleRepo::ScheduleRepo(shared_ptr<Dependency> dependency_injector) {
    mImpl = make_unique<Impl>(dependency_injector);
}

ScheduleRepo::~ScheduleRepo() {


}


