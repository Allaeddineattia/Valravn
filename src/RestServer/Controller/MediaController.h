//
// Created by alro on 18‏/4‏/2021.
//

//
// Created by alro on 16‏/1‏/2021.
//

#ifndef MYPROJECT_MEDIACONTROLLER_H
#define MYPROJECT_MEDIACONTROLLER_H


#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/data/stream/FileStream.hpp"
#include "RestServer/dto/output/ImageDTO.h"
#include "RestServer/dto/output/VideoDTO.h"
#include "RestServer/dto/input/MediaUploadDto.h"
#include "oatpp/web/mime/multipart/FileStreamProvider.hpp"
#include "oatpp/web/mime/multipart/Reader.hpp"
#include "oatpp/web/mime/multipart/PartList.hpp"
#include "oatpp/web/mime/multipart/InMemoryPartReader.hpp"
#include "../dto/StatusDto.h"
#include <Shared/CustomError.h>
#include <iostream>
#include <cstdio>
#include<fstream>
#include <Shared/StorageManager.h>
#include<ctime>
#include <Shared/DependencyInjector.h>
#include <thread>
#include <RestServer/services/MediaServices.h>
#include <unistd.h>
#include <RestServer/dto/input/AddToPlaylist.h>
#define DOWNLOAD_PATH "/home/alro/"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
namespace multipart = oatpp::web::mime::multipart;
/**
 * Media REST controller.
 */



class MediaController : public oatpp::web::server::api::ApiController {
public:
    MediaController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {
        service = make_unique<MediaServices>();
    }

    shared_ptr<VLC_Wrapper> vlcWrapper;
    shared_ptr<DependencyInjector> di;
    unique_ptr<MediaServices> service;
    void setVlc(shared_ptr<VLC_Wrapper> _vlcWrapper){
        vlcWrapper = move(_vlcWrapper);
    };

    void setDi(shared_ptr<DependencyInjector> _di) {
        di = move(_di);
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

        /* Prepare multipart container. */
        auto multipart = std::make_shared<multipart::PartList>(request->getHeaders());

        /* Create multipart reader. */
        multipart::Reader multipartReader(multipart.get());
        std::time_t t = std::time(nullptr);
        string temp_path = DOWNLOAD_PATH + to_string(t) + "temp";

        /* Configure to stream part with name "part1" to file */
        multipartReader.setPartReader("file", multipart::createFilePartReader(temp_path.c_str()));
        multipartReader.setPartReader("resolution", multipart::createInMemoryPartReader(256 /* max-data-size */));
        /* Read multipart body */
        request->transferBody(&multipartReader);

        /* Print value of "part1" */
        auto part1 = multipart->getNamedPart("file");

        /* Assert part is not null */
        OATPP_ASSERT_HTTP(part1, Status::CODE_400, "file is null");

        /* Get part data input stream */
        auto inputStream = part1->getInputStream();

        string fileName = to_string(t) + "-" + part1->getFilename()->std_str() ;
        auto resolution = multipart->getNamedPart("resolution");
        auto type = multipart->getNamedPart("type");
        auto resolutionValue = resolution->getInMemoryData()->std_str();
        auto headers = part1->getHeaders();

        auto fef = headers.getAll();
        auto contentType = fef.find("Content-Type")->second.std_str();
        // TODO - process file stream.



        //return createResponse(Status::CODE_200, "OK");
        string path = DOWNLOAD_PATH + fileName;
        if (rename(temp_path.c_str(), path.c_str()) == 0){
            size_t size = StorageManager::get_file_size(path);
            if(size > 0){
                if (contentType.find("image") != std::string::npos){
                    auto image = MediaUploadDto::createImageFromDto(path, contentType, resolutionValue, size);
                    image->save();
                    Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
                    return createDtoResponse(Status::CODE_200, dto);
                }
                if(contentType.find("video") != std::string::npos ){
                    auto duration = vlcWrapper->getDurationOfMedia(path);
                    auto video = MediaUploadDto::createVideoFromDto(path, contentType, resolutionValue, size, duration);
                    video->save();
                    Object<VideoDTO> dto(VideoDTO::createDtoFromEntity(*video));
                    return createDtoResponse(Status::CODE_200, dto);
                }
            }
        }else{
            remove(temp_path.c_str());
            cout<<"removed"<<endl;
            string error_msg = "could not create the file with the name: " + fileName;
            return handleError(Status::CODE_500, error_msg.c_str());
        }


        //Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
        Object<ImageDto> dto;
        return createDtoResponse(Status::CODE_200, dto);
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
        string type = mediaDto->mimeType->std_str();
        unsigned int id = mediaDto->id;
        if (type.find("image") != std::string::npos ){
            auto optional = Image::fetchById(id);
            if(! optional.has_value()){
                string error_msg = "no element found with mimetype <" + type + "> and id " + to_string(id) + " not supported";
                return handleError(Status::CODE_404, error_msg.data());
            }
            auto image = move(optional.value());
            image->play();
            Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
            return createDtoResponse(Status::CODE_200, dto);
        }
        else if (type.find("video") != std::string::npos ){
            auto optional = Video::fetchById(id);
            if(! optional.has_value()){
                string error_msg = "no element found with mimetype <" + type + "> and id <" + to_string(id) + " >";
                return handleError(Status::CODE_404, error_msg.data());
            }
            auto video = move(optional.value());
            Object<VideoDTO> dto(VideoDTO::createDtoFromEntity(*video));
            service->play_video(move(video), di);

            return createDtoResponse(Status::CODE_200, dto);

        }
        string error_msg = "mime type <" + type + "> not supported";
        return handleError(Status::CODE_404, error_msg.data());
    }

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
        Object<VideoDTO> * dto;
        int size = mediaDto->size;
        if(size != mediaDto->medias->size()){
            string error_msg = "size field <"+ to_string(size) +"> doesn't match with the size of the array <" + to_string( mediaDto->medias->size()) +">";
            return handleError(Status::CODE_500, error_msg.data());
        }
        for(auto & item: *mediaDto->medias){
            cout<<"-----item----"<<endl;
            cout<<item->mediaId<<endl;
            cout<<item->position<<endl;
            cout<<item->mimeType->c_str()<<endl;

            string type = item->mimeType->std_str();
            unsigned int id = item->mediaId;
            if (type.find("image") != std::string::npos ){
                auto optional = Image::fetchById(id);
                if(! optional.has_value()){
                    string error_msg = "no element found with mimetype <" + type + "> and id " + to_string(id) + " not supported";
                    return handleError(Status::CODE_404, error_msg.data());
                }
                auto image = move(optional.value());
                image->play();
                Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
                return createDtoResponse(Status::CODE_200, dto);
            }
            else if (type.find("video") != std::string::npos ){
                auto optional = Video::fetchById(id);
                if(! optional.has_value()){
                    string error_msg = "no element found with mimetype <" + type + "> and id <" + to_string(id) + " >";
                    return handleError(Status::CODE_404, error_msg.data());
                }
                auto video = move(optional.value());
                auto stateHandler = make_unique<VideoStateHandler>(di, *video);
                video->setStateHandler(move(stateHandler));
                dto = new Object<VideoDTO>(VideoDTO::createDtoFromEntity(*video));
                auto parameter = make_unique<Parameter>(true, 50, 100, 0.5);
                service->playlist->addMediaDisplay(make_unique<MediaDisplay>(move(video), move(parameter)));


            }
        }
        cout<<"playing"<<endl;
        vlcWrapper->onMediaEnd(service->playlist.get());
        service->playlist->play();
        return createDtoResponse(Status::CODE_200, *dto);
    }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //MYPROJECT_MEDIACONTROLLER_H

