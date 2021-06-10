//
// Created by alro on 16‏/1‏/2021.
//

#ifndef MYPROJECT_IMAGECONTROLLER_H
#define MYPROJECT_IMAGECONTROLLER_H


#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/data/stream/FileStream.hpp"
#include "RestServer/dto/output/ImageDTO.h"
#include "oatpp/web/mime/multipart/FileStreamProvider.hpp"
#include "oatpp/web/mime/multipart/Reader.hpp"
#include "oatpp/web/mime/multipart/PartList.hpp"
#include "oatpp/web/mime/multipart/InMemoryPartReader.hpp"
#include "../dto/StatusDto.h"
#include <Shared/CustomError.h>
#include <iostream>
#include <cstdio>
#include<fstream>
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
namespace multipart = oatpp::web::mime::multipart;
/**
 * Image REST controller.
 */



class ImageController : public oatpp::web::server::api::ApiController {
public:
    ImageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
            {}

public:

    static std::shared_ptr<ImageController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<ImageController>(objectMapper);
    }

    ENDPOINT_INFO(putImage) {
        info->summary = "Update Image by imageId";

        info->addConsumes<Object<ImageDto>>("application/json");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["imageId"].description = "Image Identifier";
    }
    ENDPOINT("PUT", "images/{imageId}", putImage,
             PATH(Int32, imageId),
             BODY_DTO(Object<ImageDto>, imageDto))
    {
        imageDto->id = imageId;
        //return createDtoResponse(Status::CODE_200, m_imageService.updateImage(imageDto));
    }


    ENDPOINT_INFO(getImageById) {
        info->summary = "Get one Image by imageId";

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["imageId"].description = "Image Identifier";
    }
    ENDPOINT("GET", "images/{imageId}", getImageById,
             PATH(Int32, imageId))
    {
        auto opt_image= Image::fetchById(imageId);
        if(opt_image.has_value() ){
            auto image = move(opt_image.value());
            if(image){
                auto dto = ImageDto::createDtoFromEntity(*image);
                return createDtoResponse(Status::CODE_200, dto);
            }
        }
        string error_msg = "image with id " + to_string(imageId) + " not found";
        return handleError(Status::CODE_404, error_msg.data());
    }


    ENDPOINT_INFO(getImages) {
        info->summary = "get all stored images";

        info->addResponse<oatpp::Vector<oatpp::Object<ImageDto>>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "images/", getImages)
    {
        auto res = Image::getAll();
        return createDtoResponse(Status::CODE_200, ImageDto::createDtoVectorFromEntities(move(res)));
    }


    ENDPOINT_INFO(deleteImage) {
        info->summary = "Delete Image by imageId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["imageId"].description = "Image Identifier";
    }
    ENDPOINT("DELETE", "images/{imageId}", deleteImage,
             PATH(Int32, imageId))
    {
        auto opt_image= Image::fetchById(imageId);
        if(opt_image.has_value() ){
            auto image = move(opt_image.value());
            if(image){
                try{
                    image->remove();
                    return createDtoResponse(Status::CODE_200,
                                             StatusDto::ok("Image was successfully deleted"));
                }catch (const std::exception& ex){
                    return handleError(Status::CODE_500,  ex.what());
                }
            }
        }
        string error_msg = "image with id " + to_string(imageId) + " not found";
        return handleError(Status::CODE_400, error_msg.data());
    }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //MYPROJECT_IMAGECONTROLLER_H
