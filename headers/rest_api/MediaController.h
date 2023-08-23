//
// Created by alro on 18‏/4‏/2021.
//

//
// Created by alro on 16‏/1‏/2021.
//

#ifndef VALRAVEN_MEDIACONTROLLER_H
#define VALRAVEN_MEDIACONTROLLER_H


#include <iostream>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <thread>
#include <unistd.h>


#include <core/Error.h>
#include <core/DependencyInjector.h>
#include <rest_api/dto/output/ImageDTO.h>
#include <rest_api/dto/output/VideoDTO.h>
#include <rest_api/dto/StatusDto.h>
#include <rest_api/dto/input/MediaUploadDto.h>
#include <rest_api/dto/input/AddToPlaylist.h>

#include <rest_api/helpers/FileUploadHandler.h>
#include <rest_api/helpers/MediaServices.h>




#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

namespace multipart = oatpp::web::mime::multipart;

/**
 * Media REST controller.
 */
class MediaController : public oatpp::web::server::api::ApiController {
public:
    explicit MediaController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {
        service = make_unique<MediaServices>();
    }

    shared_ptr<VLC_Wrapper> vlcWrapper;
    shared_ptr<DependencyInjector> di;
    unique_ptr<MediaServices> service;
    void setVlc(shared_ptr<VLC_Wrapper> _vlcWrapper){
        vlcWrapper = std::move(_vlcWrapper);
    };

    void setDi(shared_ptr<DependencyInjector> _di) {
        di = std::move(_di);
    }




public:

    static std::shared_ptr<MediaController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<MediaController>(objectMapper);
    }

    ENDPOINT_INFO(uploadMedia) {
        info->summary = "Create new Media";

        info->addConsumes < Object < MediaUploadDto >> ("multipart/form-data");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<VideoDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "media", uploadMedia,
             REQUEST(std::shared_ptr<IncomingRequest>, request))
    {

        FileUploadHandler file_downloader(request);
        try
        {
            file_downloader.store();
            if (file_downloader.get_content_type().find("image") != std::string::npos) {
                return createDtoResponse(Status::CODE_200, file_downloader.save_as_image());
            }
            if (file_downloader.get_content_type().find("video") != std::string::npos) {
                time_t duration = vlcWrapper->get_media_duration(file_downloader.get_storage_path());
                return createDtoResponse(Status::CODE_200, file_downloader.save_as_video(duration));
            }
            string error_msg = "content type not supported of the file : ";
            error_msg += file_downloader.get_content_type();
            throw error_msg;
        }
        catch(const std::string& error_message)
        {
            file_downloader.remove();
            return createResponse(Status::CODE_500, error_message.c_str());
        }


    }

    ENDPOINT_INFO(playMedia) {
        info->summary = "Play media";

        info->addConsumes<Object<PlayMediaDto>>("application/json");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<VideoDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "media/play", playMedia, BODY_DTO(Object<PlayMediaDto>, mediaDto))
    {
        string type = mediaDto->mimeType;
        unsigned int id = mediaDto->id;

        if (type.find("image") != std::string::npos ){
            optional<unique_ptr<Image>> optional = Image::fetch_by_id(id);
            if(! optional.has_value()){
                string error_msg = "no element found with mimetype <" + type + "> and id " + to_string(id) + " not supported";
                return createResponse(Status::CODE_404, error_msg.data());
            }
            unique_ptr<Image> image = std::move(optional.value());
            image->play();
            Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
            return createDtoResponse(Status::CODE_200, dto);
        }
        if (type.find("video") != std::string::npos ){
            auto optional = Video::fetch_by_id(id);
            if(! optional.has_value()){
                string error_msg = "no element found with mimetype <" + type + "> and id <" + to_string(id) + " >";
                return createResponse(Status::CODE_404, error_msg.data());
            }
            unique_ptr<Video> video = std::move(optional.value());
            Object<VideoDTO> dto(VideoDTO::createDtoFromEntity(*video));
            service->play_video(std::move(video), di);
            return createDtoResponse(Status::CODE_200, dto);
        }
        string error_msg = "mime type <" + type + "> not supported";
        return createResponse(Status::CODE_404, error_msg.data());
    }

    /*
    ENDPOINT_INFO(playlistAdd) {
        info->summary = "add medias to PlayList";

        info->addConsumes<Object<AddMediaToPlaylist>>("application/json");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<VideoDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "playlist/", playlistAdd, BODY_DTO(Object<AddMediaToPlaylist>, mediaDto))
    {

        int size = mediaDto->size;
        if(size != mediaDto->medias->size()){
            string error_msg = "size field <"+ to_string(size) +"> doesn't match with the size of the array <" + to_string( mediaDto->medias->size()) +">";
            return createResponse(Status::CODE_500, error_msg.data());
        }
        Object <VideoDTO> *dto = nullptr;
        for(Object<PlayListItem> & item: *mediaDto->medias){
            cout<<"-----item----"<<endl;
            cout<<item->mediaId<<endl;
            cout<<item->position<<endl;
            cout<<item->mimeType->c_str()<<endl;

            string type = item->mimeType;
            unsigned int id = item->mediaId;
            if (type.find("image") != std::string::npos ){
                auto optional = Image::fetchById(id);
                if(! optional.has_value()){
                    string error_msg = "no element found with mimetype <" + type + "> and id " + to_string(id) + " not supported";
                    return createResponse(Status::CODE_404, error_msg.data());
                }
                auto image = std::move(optional.value());
                image->play();
                Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));

            }
            else if (type.find("video") != std::string::npos ){
                auto optional = Video::fetchById(id);
                if(! optional.has_value()){
                    string error_msg = "no element found with mimetype <" + type + "> and id <" + to_string(id) + " >";
                    return createResponse(Status::CODE_404, error_msg.data());
                }
                auto video = std::move(optional.value());
                auto stateHandler = make_unique<VideoStateHandler>(di, *video);
                video->setStateHandler(move(stateHandler));
                dto = new Object<VideoDTO>(VideoDTO::createDtoFromEntity(*video));
                auto parameter = make_unique<Parameter>(true, 50, 100, 0.5);
                service->playlist->addMediaDisplay(make_unique<MediaDisplay>(move(video), move(parameter)));

                cout<<"playing"<<endl;
                vlcWrapper->onMediaEnd(service->playlist.get());
                service->playlist->play();
            }
        }

        return createDtoResponse(Status::CODE_200, "created");

    }*/

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //VALRAVEN_MEDIACONTROLLER_H

