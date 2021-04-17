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
#include "RestServer/dto/input/ImageCreationDto.h"
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

size_t get_file_size(string_view file_path){
    try {
        ifstream in_file(file_path.data(), ios::binary);
        in_file.seekg(0, ios::end);
        int file_size = in_file.tellg();
        cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes"<<endl;
        return file_size;
    }catch( exception & e){
        cout<<e.what()<<endl;
        return -1 ;
    }
}

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

    ENDPOINT_INFO(uploadImage) {
        info->summary = "Upload new Image";

        info->addConsumes<oatpp::swagger::Binary>("application/octet-stream");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "/upload", uploadImage, REQUEST(std::shared_ptr<IncomingRequest>, request)) {
        oatpp::data::stream::FileOutputStream fileOutputStream("/home/alro/file");
        request->transferBodyToStream(&fileOutputStream); // transfer body chunk by chunk
        for(auto l : request->getHeaders().getAll()) {
            cout<<l.first.toString()->c_str()<<", "<<l.second.toString()->c_str()<<endl;
        }

        return createResponse(Status::CODE_200, "OK");
    }

    ENDPOINT_INFO(createImage) {
        info->summary = "Create new Image";

        info->addConsumes < Object < ImageCreationDto >> ("multipart/form-data");

        info->addResponse<Object<ImageDto>>(Status::CODE_200, "application/json");

        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "images", createImage,
             REQUEST(std::shared_ptr<IncomingRequest>, request))
    {

        /* Prepare multipart container. */
        auto multipart = std::make_shared<multipart::PartList>(request->getHeaders());

        /* Create multipart reader. */
        multipart::Reader multipartReader(multipart.get());

        /* Configure to stream part with name "part1" to file */
        multipartReader.setPartReader("file", multipart::createFilePartReader("/home/alro/temp"));
        multipartReader.setPartReader("resolution", multipart::createInMemoryPartReader(256 /* max-data-size */));
        /* Read multipart body */
        request->transferBody(&multipartReader);

        /* Print value of "part1" */
        auto part1 = multipart->getNamedPart("file");

        /* Assert part is not null */
        OATPP_ASSERT_HTTP(part1, Status::CODE_400, "file is null");

        /* Get part data input stream */
        auto inputStream = part1->getInputStream();
        string fileName = part1->getFilename()->std_str();
        //cout<<"type"<< part1->g<<endl;
        auto resolution = multipart->getNamedPart("resolution");
        auto type = multipart->getNamedPart("type");
        auto resolutionValue = resolution->getInMemoryData()->std_str();
        auto headers = part1->getHeaders();

        auto fef = headers.getAll();
        auto contentType = fef.find("Content-Type")->second.std_str();
        // TODO - process file stream.


        //return createResponse(Status::CODE_200, "OK");
        string path = "/home/alro/" + fileName;
        if (rename("/home/alro/temp", path.c_str()) == 0){
            size_t size = get_file_size(path);
            if(size > 0){
                if (contentType.find("image") != std::string::npos){
                    auto image = ImageCreationDto::createEntityFromDto(path, contentType, resolutionValue, size);
                    Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
                    return createDtoResponse(Status::CODE_200, dto);
                }
                if(contentType.find("video") != std::string::npos ){
                    cout<<"this is a video "<<endl;
                }
            }
        }else{
            remove("/home/alro/temp");
            cout<<"removed"<<endl;
            string error_msg = "could not create the file with the name: " + fileName;
            return handleError(Status::CODE_500, error_msg.c_str());
        }


        //Object<ImageDto> dto(ImageDto::createDtoFromEntity(*image));
        Object<ImageDto> dto;
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
