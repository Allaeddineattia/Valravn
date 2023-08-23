//
// Created by alro on 16‏/1‏/2021.
//

#ifndef VALRAVEN_IMAGEDTO_H
#define VALRAVEN_IMAGEDTO_H

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include <image/Image.h>
#include "MultimediaDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class ImageDto : public oatpp::DTO {

    DTO_INIT(ImageDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, resolution);
    DTO_FIELD(Object<MultimediaDto> , mulitmedia);


public:
    static Object<ImageDto> createDtoFromEntity(const Image & image){
        Object<ImageDto> dto ;
        dto->id = image.get_id();
        dto->resolution = image.get_resolution().data();
        dto->mulitmedia = MultimediaDto::createDtoFromEntity(image.get_multimedia());
        return {dto};
    }

    static oatpp::List<oatpp::Object<ImageDto>> createDtoVectorFromEntities(vector<unique_ptr<Image>> images){
        oatpp::List<oatpp::Object<ImageDto>> listOfDto;
        for (unique_ptr<Image> & image : images){
            if(image){
                Object<ImageDto> dto = ImageDto::createShared();
                dto->id = image->get_id();
                dto->resolution = image->get_resolution().data();
                dto->mulitmedia = MultimediaDto::createDtoFromEntity(image->get_multimedia());
                listOfDto->push_back(dto);
            }
        }
        return listOfDto;
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //VALRAVEN_IMAGEDTO_H
