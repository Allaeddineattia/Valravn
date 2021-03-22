//
// Created by alro on 17‏/1‏/2021.
//

#ifndef MYPROJECT_IMAGECREATIONDTO_H
#define MYPROJECT_IMAGECREATIONDTO_H

#include <Entity/Contract/Image.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "MultimediaInputDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class ImageCreationDto : public oatpp::DTO {

    DTO_INIT(ImageCreationDto, DTO)
    DTO_FIELD(String, resolution) = "";
    DTO_FIELD(Object<MultimediaInputDto> , mulitmedia);


public:
    unique_ptr<Image> createEntityFromDto (){
        unsigned int newId = Image::generateNewId();
        return make_unique<Image>(newId, this->resolution->c_str(), this->mulitmedia->createEntityFromDto());
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //MYPROJECT_IMAGECREATIONDTO_H
