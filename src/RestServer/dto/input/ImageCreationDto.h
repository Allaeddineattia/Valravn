//
// Created by alro on 17‏/1‏/2021.
//

#ifndef MYPROJECT_IMAGECREATIONDTO_H
#define MYPROJECT_IMAGECREATIONDTO_H

#include <Entity/Contract/Image.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "MultimediaInputDto.h"
#include "oatpp-swagger/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class ImageCreationDto : public oatpp::DTO {

    DTO_INIT(ImageCreationDto, DTO)

   // DTO_FIELD(Object<MultimediaInputDto> , mulitmedia);
    DTO_FIELD(oatpp::swagger::Binary , file);
    DTO_FIELD(String, resolution) = "";


public:
    static unique_ptr<Image> createEntityFromDto (string_view _path, string_view _type, string_view _resolution, unsigned int _size){
        unsigned int newImageId = Image::generateNewId();
        unsigned int newMultimediaId = Multimedia::generateNewId();
        auto multimedia = make_unique<Multimedia>(newMultimediaId , _path, _size, _type);
        return make_unique<Image>(newImageId, _resolution, move(multimedia));
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //MYPROJECT_IMAGECREATIONDTO_H
