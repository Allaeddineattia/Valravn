//
// Created by rawaa on 20‏/12‏/2020.
//


#include <Entity/DependencyInjector.h>
#include "DataBase/Contracts/Repos/VideoRepo.h"

class VideoRepo::Impl{

private:
    shared_ptr<DataBase > dataBase = nullptr;
    shared_ptr<IRepository<Multimedia>> multimediaRepo = nullptr;
    string tableName =  "VIDEO";

    string getCreateTableSql() {
        return "CREATE TABLE " + tableName + "("\
                "ID INT PRIMARY KEY NOT NULL,"\
                "MULTIMEDIA_ID INT NOT NULL,"\
                "RESOLUTION TEXT NOT NULL,"\
                "DURATION INT NOT NULL,"\
                "FOREIGN KEY(MULTIMEDIA_ID) REFERENCES " + multimediaRepo->getTableName() + "(ID)"\
                ");";
    }

    [[nodiscard]] static string_map getStringMap(const Video& video) {
        string_map map;
        map.insert(string_pair("ID", to_string(video.getId())));
        map.insert(string_pair("MULTIMEDIA_ID", to_string(video.getMultimedia()->getId())));
        map.insert(string_pair("RESOLUTION" , DataBase::to_sql_string(video.getResolution())));
        map.insert(string_pair("DURATION", to_string(video.getDuration())));
        return map;
    }

    [[nodiscard]] static string_map getUpdateStringMap(const Video& oldElement, const Video& newElement) {
        string_map map;

        if(newElement.getResolution() != oldElement.getResolution())
            map.insert(string_pair("RESOLUTION", DataBase::to_sql_string(newElement.getResolution())));

        if(newElement.getDuration() != oldElement.getDuration())
            map.insert(string_pair("DURATION", to_string(newElement.getDuration())));



        return map;
    }

    [[nodiscard]] unique_ptr<Video> getEntityFromMap(const string_map &map) {
        int  id = stoi(map.find("ID")->second);
        int  duration = stoi(map.find("DURATION")->second);
        string resolution = map.find("RESOLUTION")->second;
        auto multimedia = multimediaRepo->getById(stoi(map.find("MULTIMEDIA_ID")->second)).value();
        return make_unique<Video>(id, duration, move(multimedia),resolution);
    }

    [[nodiscard]] bool createElement(const Video& element) const {
        if(multimediaRepo->save((const Multimedia &) element.getMultimedia())){
            string_map map = getStringMap(element);
            return dataBase->insert_into_table(tableName, map);
        }
        return false;
    }

    [[nodiscard]] bool updateElement(const Video& old_element, const Video& new_element) const {
        string_map map = getUpdateStringMap(old_element, new_element);
        bool result;
        if(!map.empty()){
            string_pair id ("ID",to_string(old_element.getId()));
            result = dataBase->update_into_table(tableName, id, map);
        }
        result = multimediaRepo->save((const Multimedia &) new_element.getMultimedia()) || result;
        return result;
    }

public:

    template<class Dependency>
    explicit Impl(shared_ptr<Dependency> dependency_injector){
        dataBase = dependency_injector->get_data_base(dependency_injector);
        multimediaRepo = dependency_injector->get_multimedia_repo(dependency_injector);
        dataBase->add_table_creation_sql(getCreateTableSql());
    }


    [[nodiscard]] const string & getTableName() {
        return tableName;
    };

    optional<unique_ptr<Video>> getById(unsigned int id) {
        auto video_map = dataBase->get_by_id(tableName, to_string(id));
        if(!video_map.empty())
            return getEntityFromMap(video_map);
        return std::nullopt;
    };

    vector<unique_ptr<Video>> getAll() {
        vector<string_map> vectorRes = dataBase->get_all(tableName);
        vector<unique_ptr<Video>> videos;
        for(auto &video_map: vectorRes) {
            auto multimedia = multimediaRepo->getById(stoi(video_map.find("MULTIMEDIA_ID")->second)); //ess2l
            if(multimedia) videos.push_back(getEntityFromMap(video_map));
        }
        return  videos;
    };

    [[nodiscard]] bool save(const Video& element) {
        auto exist = getById(element.getId());
        if(exist.has_value())
            return updateElement(*exist.value(), element);
        return createElement(element);
    };

    bool deleteById(unsigned int id) {
        string_pair feature_selection("ID", to_string(id));
        auto video = getById(id);
        if(!video.has_value()){
            throw "No Element found with id ";
        }
        bool result = dataBase->begin_transaction();
        result = result && dataBase->delete_by_feature(tableName, feature_selection);
        if(result)
            result = multimediaRepo->deleteById(video.value()->getMultimedia()->getId());
        return result && dataBase->end_transaction();
    }


};

const string &VideoRepo::getTableName() const {
    return mImpl->getTableName();
}

optional<unique_ptr<Video>> VideoRepo::getById(unsigned int id) {
    return mImpl->getById(id);
}

vector<unique_ptr<Video>> VideoRepo::getAll() {
    return mImpl->getAll();
}

bool VideoRepo::save(const Video &element) {
    return mImpl->save(element);
}

bool VideoRepo::deleteById(unsigned int id) {
    return mImpl->deleteById(id);
}

template<class Dependency>
VideoRepo::VideoRepo(shared_ptr<Dependency> dependency_injector) {
    mImpl = make_unique<Impl>(dependency_injector);
}

VideoRepo::~VideoRepo() {

}

namespace DO_NOT_EXECUTE{
    void conf_template_ad_repo(){
        auto di = std::make_shared<DependencyInjector>();
        ImageRepo a(di);
    }
}
