//
// Created by alro on 22‏/4‏/2021.
//

#ifndef VALRAVEN_VIDEOCONTROLLER_H
#define VALRAVEN_VIDEOCONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/data/stream/FileStream.hpp"

#include "oatpp/web/mime/multipart/FileProvider.hpp"
#include "oatpp/web/mime/multipart/Reader.hpp"
#include "oatpp/web/mime/multipart/PartList.hpp"

#include <rest_api/dto/output/VideoDTO.h>
#include <rest_api/dto/StatusDto.h>
#include <core/Error.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
namespace multipart = oatpp::web::mime::multipart;
/**
 * Video REST controller.
 */



class VideoController : public oatpp::web::server::api::ApiController {
public:
    VideoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}

public:

    static std::shared_ptr<VideoController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<VideoController>(objectMapper);
    }

    ENDPOINT_INFO(putVideo) {
        info->summary = "Update Video by videoId";

        info->addConsumes<Object<VideoDTO>>("application/json");

        info->addResponse<Object<VideoDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["videoId"].description = "Video Identifier";
    }
    ENDPOINT("PUT", "videos/{videoId}", putVideo,
             PATH(Int32, videoId),
             BODY_DTO(Object<VideoDTO>, videoDto))
    {
        videoDto->id = videoId;
        //return createDtoResponse(Status::CODE_200, m_videoService.updateVideo(videoDto));
    }


    ENDPOINT_INFO(getVideoById) {
        info->summary = "Get one Video by videoId";

        info->addResponse<Object<VideoDTO>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["videoId"].description = "Video Identifier";
    }
    ENDPOINT("GET", "videos/{videoId}", getVideoById,
             PATH(Int32, videoId))
    {
        auto opt_video= Video::fetchById(videoId);
        if(opt_video.has_value() ){
            auto video = std::move(opt_video.value());
            if(video){
                auto dto = VideoDTO::createDtoFromEntity(*video);
                return createDtoResponse(Status::CODE_200, dto);
            }
        }
        string error_msg = "video with id " + to_string(videoId) + " not found";
        return createResponse(Status::CODE_404, error_msg.data());
    }


    ENDPOINT_INFO(getVideos) {
        info->summary = "get all stored videos";

        info->addResponse<oatpp::Vector<oatpp::Object<VideoDTO>>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "videos/", getVideos)
    {
        auto res = Video::getAll();
        return createDtoResponse(Status::CODE_200, VideoDTO::createDtoVectorFromEntities(std::move(res)));
    }


    ENDPOINT_INFO(deleteVideo) {
        info->summary = "Delete Video by videoId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["videoId"].description = "Video Identifier";
    }
    ENDPOINT("DELETE", "videos/{videoId}", deleteVideo,
             PATH(Int32, videoId))
    {
        auto opt_video= Video::fetchById(videoId);
        if(opt_video.has_value() ){
            auto video = std::move(opt_video.value());
            if(video){
                try{
                    video->remove();
                    return createDtoResponse(Status::CODE_200,
                                             StatusDto::ok("Video was successfully deleted"));
                }catch (const std::exception& ex){
                    return createResponse(Status::CODE_500,  ex.what());
                }
            }
        }
        string error_msg = "video with id " + to_string(videoId) + " not found";
        return createResponse(Status::CODE_400, error_msg.data());
    }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //VALRAVEN_VIDEOCONTROLLER_H
