//
// Created by alro on 28‏/11‏/2020.
//

#ifndef MYPROJECT_MULTIMEDIAREPO_H
#define MYPROJECT_MULTIMEDIAREPO_H
#include <string>
#include <sstream>
#include <DataBase/Contracts/DataBase.h>
#include <Entity/Multimedia.h>

using namespace std;


class MultimediaRepo {
private:
    shared_ptr<DataBase > data_base = nullptr;

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
        map.insert(string_pair("PATH", to_sql_string(multimedia.getPath())));
        map.insert(string_pair("SIZE",to_string(multimedia.getSize())));
        map.insert(string_pair("MIME_TYPE" , to_sql_string(multimedia.getMimeType())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Multimedia& old_element, const Multimedia& new_element) {
        string_map map;

        if(new_element.getPath() != old_element.getPath())
            map.insert(string_pair("PATH", to_sql_string(new_element.getPath())));

        if(new_element.getSize() != old_element.getSize())
            map.insert(string_pair("SIZE",to_string(new_element.getSize())));

        if(new_element.getMimeType() != old_element.getMimeType())
            map.insert(string_pair("MIME_TYPE" , to_sql_string(new_element.getMimeType())));

        return map;
    }

    [[nodiscard]] static unique_ptr<Multimedia> get_entity_from_map( const string_map & map) {
        unsigned int  id = stoi(map.find("ID")->second);
        time_t size = stoi(map.find("SIZE")->second);
        auto result = make_unique<Multimedia>( id, map.find("PATH")->second,  size,  map.find("MIME_TYPE")->second) ;
        return result;
    }

    [[nodiscard]] bool create_element(const Multimedia& element) const {
        string_map map = get_string_map(element);
        return data_base->insert_into_table(table_name, map);

    }

    [[nodiscard]] bool update_element(const Multimedia& old_element, const Multimedia& new_element) const {

        string_map map = get_update_string_map(old_element, new_element);
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.getId()));
            return data_base->update_into_table(table_name, id, map);
        }
        return false;
    }

public:
    template<class Dependency>
    explicit MultimediaRepo(Dependency dependency_injector){
        data_base = dependency_injector->get_data_base(dependency_injector);
        data_base->add_table_creation_sql(get_create_table_sql());
    };

    [[nodiscard]] const string & get_table_name() const{
        return table_name;
    };

    unique_ptr<Multimedia> get_by_id(unsigned int id){
        string_map map = data_base->get_by_id(table_name, to_string(id));
        if( map.empty())  return nullptr;
        return get_entity_from_map(map);


    };

    [[nodiscard]] static vector<unique_ptr<Multimedia>> get_all() {
        vector<unique_ptr<Multimedia>> multimedia;
        return  multimedia;
    };

    bool save(const Multimedia& element) {
        auto exist = get_by_id(element.getId());
        if(exist == nullptr)
            return create_element(element);
        return update_element(*exist, element);
    };

    bool delete_by_id(unsigned int id) {
        string_pair feature_selection("ID",to_string(id));
        return data_base->delete_by_feature(table_name, feature_selection);
    }
};


#endif //MYPROJECT_MULTIMEDIAREPO_H
