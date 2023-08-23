//
// Created by alro on 16‏/1‏/2021.
//

#ifndef VALRAVEN_IMAGECONTROLLER_H
#define VALRAVEN_IMAGECONTROLLER_H


#include <iostream>
#include <cstdio>
#include <fstream>

#include <rest_api/dto/output/ImageDTO.h>
#include <rest_api/dto/StatusDto.h>
#include <oatpp/web/mime/multipart/Multipart.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
namespace multipart = oatpp::web::mime::multipart;
/**
 * Image REST controller.
 */



class ImageController : public oatpp::web::server::api::ApiController {
public:
    explicit ImageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
            {}

public:

    static std::shared_ptr<ImageController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<ImageController>(objectMapper);
    }

    ENDPOINT_INFO(putImage)
    {
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


    ENDPOINT_INFO(getImageById)
    {
        info->summary = "Get one Image by imageId";
        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        info->pathParams["imageId"].description = "Image Identifier";
    }
    ENDPOINT("GET", "images/{imageId}", getImageById,
             PATH(Int32, imageId))
    {
        optional<unique_ptr<Image>> opt_image= Image::fetch_by_id(imageId);
        if(opt_image.has_value() ){
            unique_ptr<Image> image = std::move(opt_image.value());
            if(image){
                Object<ImageDto> dto = ImageDto::createDtoFromEntity(*image);
                return createDtoResponse(Status::CODE_200, dto);
            }
        }
        string error_msg = "image with id " + to_string(imageId) + " not found";
        return createResponse(Status::CODE_404, error_msg.data());
    }


    ENDPOINT_INFO(getImages) {
        info->summary = "get all stored images";

        info->addResponse<oatpp::Vector<oatpp::Object<ImageDto>>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "images/", getImages)
    {
        vector<unique_ptr<Image>> images = Image::get_all();
        return createDtoResponse(Status::CODE_200, ImageDto::createDtoVectorFromEntities(std::move(images)));
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
        auto opt_image= Image::fetch_by_id(imageId);
        if(opt_image.has_value() ){
            auto image = std::move(opt_image.value());
            if(image){
                try{
                    image->remove();
                    return createDtoResponse(Status::CODE_200,
                                             StatusDto::ok("Image was successfully deleted"));
                }catch (const std::exception& ex){
                    return createResponse(Status::CODE_500,  ex.what());
                }
            }
        }
        string error_msg = "image with id " + to_string(imageId) + " not found";
        return createResponse(Status::CODE_400, error_msg.data());
    }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen


#endif //VALRAVEN_IMAGECONTROLLER_H
