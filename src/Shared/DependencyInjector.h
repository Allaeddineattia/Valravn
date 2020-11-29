//
// Created by alro on 29‏/11‏/2020.
//

#ifndef MYPROJECT_DEPENDENCYINJECTOR_H
#define MYPROJECT_DEPENDENCYINJECTOR_H

#include <DataBase/Contracts/DataBase.h>
#include <DataBase/Contracts/Repos/MultimediaRepo.h>
#include <cassert>
#include <DataBase/Contracts/Repos/ImageRepo.h>

class DependencyInjector {
private:
    unique_ptr<DataBase> data_base = nullptr;
    unique_ptr<MultimediaRepo> multimedia_repo = nullptr;
    unique_ptr<ImageRepo> image_repo = nullptr;

public:
    DependencyInjector()= default;

    bool install_data_base(string_view db_path){
        assert(!data_base);
        data_base = make_unique<DataBase>(db_path);
        return true;
    }
    shared_ptr<DataBase> get_data_base(const shared_ptr<DependencyInjector>& d){
        assert(data_base);
        return shared_ptr<DataBase>(d, data_base.get());
    }

    bool install_multimedia_repo(const shared_ptr<DependencyInjector>& d){
        assert(!multimedia_repo);
        multimedia_repo = make_unique<MultimediaRepo>(d);
        return true;
    };
    shared_ptr<MultimediaRepo> get_multimedia_repo(const shared_ptr<DependencyInjector>& d){
        assert(multimedia_repo);
        return shared_ptr<MultimediaRepo>(d, multimedia_repo.get());
    };

    bool install_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(!image_repo);
        image_repo = make_unique<ImageRepo>(d);
        return true;
    }
    shared_ptr<ImageRepo> get_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(image_repo);
        return shared_ptr<ImageRepo>(d, image_repo.get());
    }


};
#endif //MYPROJECT_DEPENDENCYINJECTOR_H
