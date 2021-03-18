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
#include "RestServer/dto/output/ImageDTO.h"
#include "RestServer/dto/input/ImageCreationDto.h"
#include "../dto/StatusDto.h"
#include <iostream>

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

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

    ENDPOINT_INFO(createImage) {
        info->summary = "Create new Image";

        info->addConsumes < Object < ImageCreationDto >> ("application/json");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "images", createImage,
             BODY_DTO(Object<ImageCreationDto>, imageDto))
    {
        std::cout<<imageDto->resolution->c_str()<<std::endl;
        std::cout<<imageDto->mulitmedia->path->c_str()<<std::endl;
        std::cout<<imageDto->mulitmedia->size<<std::endl;
        std::cout<<imageDto->mulitmedia->mimeType->c_str()<<std::endl;
        auto image = imageDto->createEntityFromDto();
        try{
            image->save();
        }catch (const std::exception& ex){
            return handleError(Status::CODE_404, ex.what());
        }

        Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));

        return createDtoResponse(Status::CODE_200, dto);
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
        //return createDtoResponse(Status::CODE_200, m_imageService.getImageById(imageId));
    }


    ENDPOINT_INFO(getImages) {
        info->summary = "get all stored images";

        //info->addResponse<oatpp::Object<ImagesPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "images/offset/{offset}/limit/{limit}", getImages,
             PATH(UInt32, offset),
             PATH(UInt32, limit))
    {
        //return createDtoResponse(Status::CODE_200, m_imageService.getAllImages(offset, limit));
    }


    ENDPOINT_INFO(deleteImage) {
        info->summary = "Delete Image by imageId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["imageId"].description = "Image Identifier";
    }
    ENDPOINT("DELETE", "images/{imageId}", deleteImage,
             PATH(Int32, imageId))
    {
        //return createDtoResponse(Status::CODE_200, m_imageService.deleteImageById(imageId));
    }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //MYPROJECT_IMAGECONTROLLER_H
