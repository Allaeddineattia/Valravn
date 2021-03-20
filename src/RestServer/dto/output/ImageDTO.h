//
// Created by alro on 16‏/1‏/2021.
//

#ifndef MYPROJECT_IMAGEDTO_H
#define MYPROJECT_IMAGEDTO_H

#include <Entity/Contract/Image.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "MultimediaDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class ImageDto : public oatpp::DTO {

    DTO_INIT(ImageDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, resolution);
    DTO_FIELD(Object<MultimediaDto> , mulitmedia);


public:
    static Object<ImageDto> createDtoFromEntity(const Image & image){
        auto dto = make_shared<ImageDto>();
        dto->id = image.getId();
        dto->resolution = image.getResolution().data();
        dto->mulitmedia = MultimediaDto::createDtoFromEntity(image.getMultimedia());
        return Object<ImageDto>(dto);
    }

    static oatpp::List<oatpp::Object<ImageDto>> createDtoVectorFromEntities(vector<unique_ptr<Image>> images){
        auto result = List<Object<ImageDto>>::createShared();
        for (auto & image : images){
            if(image){
                auto dto = ImageDto::createShared();
                dto->id = image->getId();
                dto->resolution = image->getResolution().data();
                dto->mulitmedia = MultimediaDto::createDtoFromEntity(image->getMultimedia());
                result->push_back(dto);
            }
        }
        return result;
    }




};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //MYPROJECT_IMAGEDTO_H
