//
// Created by alro on 29‏/11‏/2020.
//

#ifndef MYPROJECT_IMAGEREPO_H
#define MYPROJECT_IMAGEREPO_H


#include <DataBase/Contracts/DataBase.h>
#include <DataBase/Contracts/Repos/MultimediaRepo.h>
#include <Entity/Image.h>
#include <optional>

class ImageRepo {
private:
    shared_ptr<DataBase >  data_base = nullptr;
    shared_ptr<MultimediaRepo> multimedia_repo = nullptr;
    string table_name =  "IMAGE";

    string get_create_table_sql() {
        return "CREATE TABLE " + table_name + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "MULTIMEDIA_ID INT NOT NULL,"\
                "RESOLUTION TEXT NOT NULL,"\
                "FOREIGN KEY(MULTIMEDIA_ID) REFERENCES " + multimedia_repo->get_table_name() + "(ID)"\
                ");";
    }

    [[nodiscard]] static string_map get_string_map(const Image& image) {
        string_map map;
        map.insert(string_pair("ID", to_string(image.getId())));
        map.insert(string_pair("MULTIMEDIA_ID", to_string(image.getMultimedia().getId())));
        map.insert(string_pair("RESOLUTION" , to_sql_string(image.getResolution())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Image& old_element, const Image& new_element) {
        string_map map;

        if(new_element.getResolution() != old_element.getResolution())
            map.insert(string_pair("RESOLUTION", to_sql_string(new_element.getResolution())));


        return map;
    }

    [[nodiscard]] unique_ptr<Image>
    get_entity_from_map(const string_map &map) {
        int  id = stoi(map.find("ID")->second);
        string resolution = map.find("RESOLUTION")->second;
        auto multimedia = multimedia_repo->get_by_id(stoi(map.find("MULTIMEDIA_ID")->second));
        return make_unique<Image>(id, resolution, move(multimedia));
    }

    [[nodiscard]] bool create_element(const Image& element) const {
        if(multimedia_repo->save(element.getMultimedia())){
            string_map map = get_string_map(element);
            return data_base->insert_into_table(table_name, map);
        }
        return false;
    }

    [[nodiscard]] bool update_element(const Image& old_element, const Image& new_element) const {
        string_map map = get_update_string_map(old_element, new_element);
        bool result;
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.getId()));
            result = data_base->update_into_table(table_name, id, map);
        }
        result = multimedia_repo->save(new_element.getMultimedia()) || result;
        return result;
    }



public:

    template<class Dependency>
    explicit ImageRepo(shared_ptr<Dependency> dependency_injector){
        data_base = dependency_injector->get_data_base(dependency_injector);
        multimedia_repo = dependency_injector->get_multimedia_repo(dependency_injector);
        data_base->add_table_creation_sql(get_create_table_sql());
    };

    [[nodiscard]] const string & get_table_name() const{
        return table_name;
    };

    optional<unique_ptr<Image>> get_by_id(unsigned int id){
        auto image_map = data_base->get_by_id(table_name, to_string(id));
        if(!image_map.empty())
            return get_entity_from_map(image_map);
        return std::nullopt;
    };

    vector<unique_ptr<Image>> get_all(){
        vector<string_map> vector_res = data_base->get_all(table_name);
        vector<unique_ptr<Image>> images;
        for(auto &image_map: vector_res) {
            auto multimedia = multimedia_repo->get_by_id(stoi(image_map.find("MULTIMEDIA_ID")->second));
            if(multimedia) images.push_back(get_entity_from_map(image_map));
        }
        return  images;
    };

    [[nodiscard]] bool save(const Image& element) {
        auto exist = get_by_id(element.getId());
        if(exist.has_value())
            return update_element(*exist.value(), element);
        return create_element(element);
    };

    bool delete_by_id(unsigned int id) {
        string_pair feature_selection("ID", to_string(id));
        auto image = get_by_id(id);
        if(!image.has_value()){
            throw "No Element found with id ";
        }
        bool result = data_base->begin_transaction();
        result = result && data_base->delete_by_feature(table_name, feature_selection);
        if(result)
            result = multimedia_repo->delete_by_id(image.value()->getMultimedia().getId());
        return result && data_base->end_transaction();
    }

};


#endif //MYPROJECT_IMAGEREPO_H
