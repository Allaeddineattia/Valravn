//
// Created by alro on 28‏/11‏/2020.
//

#include <media_player/MultimediaRepo.h>
#include <core/DependencyInjector.h>

using namespace DataBase;

class MultimediaRepo::Impl{
private:
    shared_ptr<SQLiteWrapper > data_base = nullptr;

    string table_name =  "MULTIMEDIA";


    string get_create_table_sql() {
        return  "CREATE TABLE " + table_name + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "PATH TEXT UNIQUE,"\
                "MIME_TYPE TEXT NOT NULL,"\
                "SIZE DURATION UNSIGNED BIG NOT NULL"\
                ");";
    }


    [[nodiscard]] static string_map get_string_map(const Multimedia & multimedia) {
        string_map map;
        map.insert(string_pair("ID",to_string(multimedia.getId())));
        map.insert(string_pair("PATH", SQLHelpers::to_sql_string(multimedia.getPath())));
        map.insert(string_pair("SIZE",to_string(multimedia.getSize())));
        map.insert(string_pair("MIME_TYPE" , SQLHelpers::to_sql_string(multimedia.getMimeType())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Multimedia& old_element, const Multimedia& new_element) {
        string_map map;

        if(new_element.getPath() != old_element.getPath())
            map.insert(string_pair("PATH", SQLHelpers::to_sql_string(new_element.getPath())));

        if(new_element.getSize() != old_element.getSize())
            map.insert(string_pair("SIZE",to_string(new_element.getSize())));

        if(new_element.getMimeType() != old_element.getMimeType())
            map.insert(string_pair("MIME_TYPE" , SQLHelpers::to_sql_string(new_element.getMimeType())));

        return map;
    }

    [[nodiscard]] static unique_ptr<Multimedia> get_entity_from_map( const string_map & map) {
        unsigned int  id = stoi(map.find("ID")->second);
        time_t size = stoi(map.find("SIZE")->second);
        auto result = make_unique<Multimedia>( id, SQLHelpers::from_sql_string(map.find("PATH")->second),  size,  map.find("MIME_TYPE")->second) ;
        return result;
    }

    void create_element(const Multimedia& element) const {
        string_map map = get_string_map(element);
        data_base->insert_into_table(table_name, map);
    }

    void update_element(const Multimedia& old_element, const Multimedia& new_element) const {
        string_map map = get_update_string_map(old_element, new_element);
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.getId()));
            data_base->update_into_table(table_name, id, map);
        }
    }



public:
    template<class Dependency>
    explicit Impl(Dependency dependency_injector){
        data_base = dependency_injector->get_data_base(dependency_injector);
        data_base->add_table_creation_sql(get_create_table_sql());
    };

    [[nodiscard]] const string & get_table_name() const{
        return table_name;
    };

    optional<unique_ptr<Multimedia>> get_by_id(unsigned int id) {
        string_map map = data_base->get_by_id(table_name, to_string(id));
        if( map.empty())  return nullptr;
        return get_entity_from_map(map);


    };

    [[nodiscard]] vector<unique_ptr<Multimedia>> get_all() {
        vector<unique_ptr<Multimedia>> multimedia;
        return  multimedia;
    };

    void save(const Multimedia& element) {
        auto exist = get_by_id(element.getId());
        if(exist.has_value()){
            auto mul = std::move(exist.value());
            if (mul){
                return update_element(*mul, element);
            }
        }
        create_element(element);
    };

    bool delete_by_id(unsigned int id)  {
        string_pair feature_selection("ID",to_string(id));
        data_base->delete_by_feature(table_name, feature_selection);
        return true;
    }

    unsigned int get_available_id() {
        return 0;
    }

};

template<class Dependency>
MultimediaRepo::MultimediaRepo(Dependency dependency_injector) {
    mImpl = make_unique<Impl>(dependency_injector);
}

const string &MultimediaRepo::getTableName() const {
    return mImpl->get_table_name();
}

optional<unique_ptr<Multimedia>> MultimediaRepo::getById(unsigned int id) {
    return mImpl->get_by_id(id);
}

vector<unique_ptr<Multimedia>> MultimediaRepo::getAll() {
    return mImpl->get_all();
}

void MultimediaRepo::save(const Multimedia &element) {
    mImpl->save(element);
}

void MultimediaRepo::deleteById(unsigned int id) {
    mImpl->delete_by_id(id);
}

MultimediaRepo::~MultimediaRepo() = default;

namespace DO_NOT_EXECUTE{
    void conf_template_multimedia_repo(){
        auto di = std::make_shared<DependencyInjector>();
        MultimediaRepo a(di);
    }
}