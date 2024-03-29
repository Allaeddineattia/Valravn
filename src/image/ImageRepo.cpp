//
// Created by alro on 29‏/11‏/2020.
//

#include <core/DependencyInjector.h>
#include <image/ImageRepo.h>

using namespace DataBase;

class ImageRepo::Impl{

private:
    shared_ptr<SQLiteWrapper >  data_base = nullptr;
    shared_ptr<IRepository<Multimedia>> multimedia_repo = nullptr;
    string table_name =  "IMAGE";

    string get_create_table_sql() {
        return "CREATE TABLE " + table_name + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "MULTIMEDIA_ID INT UNIQUE,"\
                "RESOLUTION TEXT NOT NULL,"\
                "FOREIGN KEY(MULTIMEDIA_ID) REFERENCES " + multimedia_repo->get_table_name() + "(ID)"\
                ");";
    }

    [[nodiscard]] static string_map get_string_map(const Image& image) {
        string_map map;
        map.insert(string_pair("ID", to_string(image.get_id())));
        map.insert(string_pair("MULTIMEDIA_ID", to_string(image.get_multimedia().get_id())));
        map.insert(string_pair("RESOLUTION" , SQLHelpers::to_sql_string(image.get_resolution())));
        return map;
    }

    [[nodiscard]] static string_map get_update_string_map(const Image& old_element, const Image& new_element) {
        string_map map;

        if(new_element.get_resolution() != old_element.get_resolution())
            map.insert(string_pair("RESOLUTION", SQLHelpers::to_sql_string(new_element.get_resolution())));


        return map;
    }

    [[nodiscard]] unique_ptr<Image> get_entity_from_map(const string_map &map) {
        int  id = stoi(map.find("ID")->second);
        string resolution = map.find("RESOLUTION")->second;
        auto multimedia = multimedia_repo->get_by_id(stoi(map.find("MULTIMEDIA_ID")->second)).value();
        return make_unique<Image>(id, resolution, move(multimedia));
    }

    void create_element(const Image& element) const {
        data_base->begin_transaction();
        try {
            multimedia_repo->save(element.get_multimedia());
            string_map map = get_string_map(element);
            data_base->insert_into_table(table_name, map);
        }catch (const std::exception& ex){
            data_base->abort_transaction();
            throw ;
        }
        data_base->end_transaction();

    }

    void update_element(const Image& old_element, const Image& new_element) const {
        string_map map = get_update_string_map(old_element, new_element);
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.get_id()));
            data_base->update_into_table(table_name, id, map);
        }
        multimedia_repo->save(new_element.get_multimedia());
    }

public:

    template<class Dependency>
    explicit Impl(shared_ptr<Dependency> dependency_injector){
        data_base = dependency_injector->get_data_base(dependency_injector);
        multimedia_repo = dependency_injector->get_multimedia_repo(dependency_injector);
        data_base->add_table_creation_sql(get_create_table_sql());
    }


    [[nodiscard]] const string & get_table_name() {
        return table_name;
    };

    optional<unique_ptr<Image>> get_by_id(unsigned int id) {
        const string_map &image_map = data_base->get_by_id(table_name, to_string(id));
        if(!image_map.empty())
        {
            return get_entity_from_map(image_map);
        }

        return std::nullopt;
    };

    vector<unique_ptr<Image>> get_all() {
        vector<string_map> vector_res = data_base->get_all(table_name);
        vector<unique_ptr<Image>> images;
        for(string_map &image_map: vector_res) {
            auto multimedia = multimedia_repo->get_by_id(stoi(image_map.find("MULTIMEDIA_ID")->second));
            if(multimedia)
            {
                images.push_back(get_entity_from_map(image_map));
            }
        }
        return  images;
    };

    void save(const Image& element) {

        optional<unique_ptr<Image>> exist = get_by_id(element.get_id());
        if(exist.has_value() && exist.value()){
            update_element(*exist.value(), element);
            return;
        }
        create_element(element);
    };

    void delete_by_id(unsigned int id) {
        string_pair feature_selection("ID", to_string(id));
        optional<unique_ptr<Image>> image = get_by_id(id);
        if(!image.has_value()){
            throw "No Element found with id ";
        }
        data_base->begin_transaction();
        try{
            data_base->delete_by_feature(table_name, feature_selection);
            multimedia_repo->delete_by_id(image.value()->get_multimedia().get_id());
        }catch (const std::exception& ex){
            data_base->abort_transaction();
            throw ;
        }

        data_base->end_transaction();
    }

};

const string &ImageRepo::get_table_name()  const {
    return mImpl->get_table_name();
}

optional<unique_ptr<Image>> ImageRepo::get_by_id(unsigned int id) {
    return mImpl->get_by_id(id);
}

vector<unique_ptr<Image>> ImageRepo::get_all() {
    return mImpl->get_all();
}

void ImageRepo::save(const Image &element) {
    mImpl->save(element);
}

void ImageRepo::delete_by_id(unsigned int id) {
    return mImpl->delete_by_id(id);
}

template<class Dependency>
ImageRepo::ImageRepo(shared_ptr<Dependency> dependency_injector) {
    mImpl = make_unique<Impl>(dependency_injector);
}

ImageRepo::~ImageRepo() = default;


namespace DO_NOT_EXECUTE{
    void conf_template_image_repo(){
        auto di = std::make_shared<DependencyInjector>();
        ImageRepo a(di);
    }
}
