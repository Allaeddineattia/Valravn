//
// Created by alro on 29‏/11‏/2020.
//

#ifndef VALRAVN_DEPENDENCY_INJECTOR_H
#define VALRAVN_DEPENDENCY_INJECTOR_H

#include <cassert>

#include <image/Image.h>
#include <playlist/Playlist.h>
#include <video/Video.h>

#include "database/SQLiteWrapper.h"
#include <media_player/MultimediaRepo.h>
#include <playlist/PlaylistRepo.h>


#include <database/IRepository.h>
#include <image/ImageRepo.h>
#include <video/VideoRepo.h>
#include <playlist/PlaylistRepo.h>
#include <media_player/VLC_Wrapper.h>

/**
 * enables the other classes to retrieve instances of the classes that they depend on.
 */
class DependencyInjector {
private:
    unique_ptr<DataBase::SQLiteWrapper> data_base = nullptr;
    unique_ptr<DataBase::IRepository<Multimedia>> multimedia_repo = nullptr;
    unique_ptr<DataBase::IRepository<Image>> image_repo = nullptr;
    unique_ptr<DataBase::IRepository<Video>> video_repo = nullptr;
    unique_ptr<DataBase::IRepository<Playlist>> playlist_repo = nullptr;
    unique_ptr<VLC_Wrapper> vlc_wrapper =  nullptr;

public:
    DependencyInjector()= default;

    bool install_data_base(string_view db_path){
        assert(!data_base);
        data_base = make_unique<DataBase::SQLiteWrapper>(db_path);
        return true;
    }
    shared_ptr<DataBase::SQLiteWrapper> get_data_base(const shared_ptr<DependencyInjector>& d){
        assert(data_base);
        return {d, data_base.get()};
    }

    bool install_multimedia_repo(const shared_ptr<DependencyInjector>& d){
        assert(!multimedia_repo);
        multimedia_repo = make_unique<DataBase::MultimediaRepo>(d);
        return true;
    };
    
    shared_ptr<DataBase::IRepository<Multimedia>> get_multimedia_repo(const shared_ptr<DependencyInjector>& d){
        assert(multimedia_repo);
        return {d, multimedia_repo.get()};
    };

    bool install_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(!image_repo);
        image_repo = make_unique<DataBase::ImageRepo>(d);
        return true;
    }
    bool install_video_repo(const shared_ptr<DependencyInjector>& d){
        assert(!video_repo);
        video_repo = make_unique<DataBase::VideoRepo>(d);
        return true;
    }
    bool install_playlist_repo(const shared_ptr<DependencyInjector>& d){
        assert(!playlist_repo);
        //playlist_repo = make_unique<PlaylistRepo>(d); //play list repo not implemented
        return true;
    }
    shared_ptr<DataBase::IRepository<Playlist>> get_playlist_repo(const shared_ptr<DependencyInjector>& d){
        assert(playlist_repo);
        //return shared_ptr<IRepository<PlaylistRepo>>(d, multimedia_repo.get()); //play list repo not implemented
    };

    shared_ptr<DataBase::IRepository<Image>> get_image_repo(const shared_ptr<DependencyInjector>& d){
        assert(image_repo);
        return {d, image_repo.get()};
    }
    shared_ptr<DataBase::IRepository<Video>> get_video_repo(const shared_ptr<DependencyInjector>& d){
        assert(video_repo);
        return {d, video_repo.get()};
    }

    bool install_vlc_wrapper(){
        assert(!vlc_wrapper);
        vlc_wrapper = make_unique<VLC_Wrapper>();
        return true;
    }
    shared_ptr<VLC_Wrapper> get_vlc_wrapper(const shared_ptr<DependencyInjector>& d){
        assert(vlc_wrapper);
        return {d, vlc_wrapper.get()};
    }


};
#endif //VALRAVN_DEPENDENCY_INJECTOR_H
