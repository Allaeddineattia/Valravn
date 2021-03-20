//
// Created by alro on 29‏/11‏/2020.
//

#ifndef MYPROJECT_DEPENDENCYINJECTOR_H
#define MYPROJECT_DEPENDENCYINJECTOR_H
#include "Image.h"
#include "Playlist.h"

#include <DataBase/Contracts/DataBase.h>
#include <DataBase/Contracts/Repos/MultimediaRepo.h>
#include <DataBase/Contracts/Repos/PlaylistRepo.h>

#include <cassert>


#include <DataBase/Contracts/IRepository.h>
#include <DataBase/Contracts/Repos/ImageRepo.h>


class DependencyInjector {
private:
    unique_ptr<DataBase> data_base = nullptr;
    unique_ptr<IRepository<Multimedia>> multimedia_repo = nullptr;
    unique_ptr<IRepository<Image>> image_repo = nullptr;
    unique_ptr<IRepository<Playlist>> playlist_repo = nullptr;

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
    
    shared_ptr<IRepository<Multimedia>> get_multimedia_repo(const shared_ptr<DependencyInjector>& d){
        assert(multimedia_repo);
        return shared_ptr<IRepository<Multimedia>>(d, multimedia_repo.get());
    };

    bool install_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(!image_repo);
        image_repo = make_unique<ImageRepo>(d);
        return true;
    }
    bool install_playlist_repo(const shared_ptr<DependencyInjector>& d){
        assert(!playlist_repo);
        playlist_repo = make_unique<PlaylistRepo>(d);
        return true;
    }
    shared_ptr<IRepository<Playlist>> get_playlist_repo(const shared_ptr<DependencyInjector>& d){
        assert(playlist_repo);
        return shared_ptr<IRepository<Playlist>>(d, multimedia_repo.get());
    };

    shared_ptr<IRepository<Image>> get_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(image_repo);
        return shared_ptr<IRepository<Image>>(d, image_repo.get());
    }


};
#endif //MYPROJECT_DEPENDENCYINJECTOR_H
