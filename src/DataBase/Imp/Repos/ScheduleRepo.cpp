//
// Created by rawaa on 25‏/12‏/2020.
//
#include <DataBase/Contracts/Repos/ScheduleRepo.h>
#include <Entity/DependencyInjector.h>
class ScheduleRepo::Impl{

private:
    shared_ptr<DataBase >  data_base = nullptr;
    shared_ptr<IRepository<Playlist>> Playlist_repo = nullptr;
    string table_name =  "Schedule";

    string get_create_table_sql() {
        return "CREATE TABLE " + table_name + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "PLAYLIST_ID INT NOT NULL,"\
                "TIME TIME NOT NULL,"\
                "FOREIGN KEY(PLAYLIST_ID) REFERENCES " + Playlist_repo->getTableName() + "(ID)"\
                ");";
    }

    [[nodiscard]] static string_map get_string_map(const Schedule& schedule) {
        string_map map;
        map.insert(string_pair("ID", to_string(schedule.getId())));
        map.insert(string_pair("PLAYLIST_ID", to_string(schedule.getPlaylist().getId())));
        map.insert(string_pair("TIME" , DataBase::to_sql_date_time(schedule.getTime())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Schedule& old_element, const   Schedule& new_element) {
        string_map map;

        if(new_element.getTime() != old_element.getTime())
            map.insert(string_pair("TIME", DataBase::to_sql_date_time(new_element.getTime())));


        return map;
    }

    [[nodiscard]] unique_ptr<Schedule> get_entity_from_map(const string_map &map) {
        int  id = stoi(map.find("ID")->second);
        string timeS = map.find("TIME")->second;
        const char * c = timeS.c_str();
        struct tm tm;
        strptime(c, "%H:%M:%S", &tm);
        time_t time = mktime(&tm);
        auto Playlist = Playlist_repo->getById(stoi(map.find("PLAYLIST_ID")->second)).value();
        return make_unique<Schedule>(id, time, move(Playlist));
    }

    [[nodiscard]] bool create_element(const Schedule& element) const {
        if(Playlist_repo->save(element.getPlaylist())){
            string_map map = get_string_map(element);
            return data_base->insert_into_table(table_name, map);
        }
        return false;
    }

    [[nodiscard]] bool update_element(const Schedule& old_element, const Schedule& new_element) const {
        string_map map = get_update_string_map(old_element, new_element);
        bool result;
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.getId()));
            result = data_base->update_into_table(table_name, id, map);
        }
        result = Playlist_repo->save(new_element.getPlaylist()) || result;
        return result;
    }

public:

    template<class Dependency>
    explicit Impl(shared_ptr<Dependency> dependency_injector){
        data_base = dependency_injector->get_data_base(dependency_injector);
        Playlist_repo = dependency_injector->get_playlist_repo(dependency_injector);
        data_base->add_table_creation_sql(get_create_table_sql());
    }


    [[nodiscard]] const string & get_table_name() {
        return table_name;
    };

    optional<unique_ptr<Schedule>> get_by_id(unsigned int id) {
        auto schedule_map = data_base->get_by_id(table_name, to_string(id));
        if(!schedule_map.empty())
            return get_entity_from_map(schedule_map);
        return std::nullopt;
    };

    vector<unique_ptr<Schedule>> get_all() {
        vector<string_map> vector_res = data_base->get_all(table_name);
        vector<unique_ptr<Schedule>> schedules;
        for(auto &schedule_map: vector_res) {
            auto Playlist = Playlist_repo->getById(stoi(schedule_map.find("MULTIMEDIA_ID")->second));
            if(Playlist) schedules.push_back(get_entity_from_map(schedule_map));
        }
        return  schedules;
    };

    [[nodiscard]] bool save(const Schedule& element) {
        auto exist = get_by_id(element.getId());
        if(exist.has_value())
            return update_element(*exist.value(), element);
        return create_element(element);
    };

    bool delete_by_id(unsigned int id) {
        string_pair feature_selection("ID", to_string(id));
        auto schedule = get_by_id(id);
        if(!schedule.has_value()){
            throw "No Element found with id ";
        }
        bool result = data_base->begin_transaction();
        result = result && data_base->delete_by_feature(table_name, feature_selection);
        if(result)
            result = Playlist_repo->deleteById(schedule.value()->getPlaylist().getId());
        return result && data_base->end_transaction();
    }


};

const string &ScheduleRepo::getTableName()  const {
    return mImpl->get_table_name();
}

optional<unique_ptr<Schedule>> ScheduleRepo::getById(unsigned int id) {
    return mImpl->get_by_id(id);
}

vector<unique_ptr<Schedule>> ScheduleRepo::getAll() {
    return mImpl->get_all();
}

bool ScheduleRepo::save(const Schedule &element) {
    return mImpl->save(element);
}

bool ScheduleRepo::deleteById(unsigned int id) {
    return mImpl->delete_by_id(id);
}

template<class Dependency>
ScheduleRepo::ScheduleRepo(shared_ptr<Dependency> dependency_injector) {
    mImpl = make_unique<Impl>(dependency_injector);
}

ImageRepo::~ImageRepo() {

}

namespace DO_NOT_EXECUTE{
    void conf_template_ad_repo(){
        auto di = std::make_shared<DependencyInjector>();
        ImageRepo a(di);
    }
}


