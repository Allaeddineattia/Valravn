//
// Created by alro on 17‏/1‏/2021.
//

#ifndef MYPROJECT_IMAGEINPUTDTO_H
#define MYPROJECT_IMAGEINPUTDTO_H

#include <Entity/Image.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "MultimediaInputDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class ImageInputDto : public oatpp::DTO {

    DTO_INIT(ImageInputDto, DTO)

    DTO_FIELD(String, resolution);
    DTO_FIELD(Object<MultimediaInputDto> , mulitmedia);


public:
    unique_ptr<Image> createEntityFromDto (){
        return make_unique<Image>(0, this->resolution->c_str(), this->mulitmedia->createEntityFromDto());
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //MYPROJECT_IMAGEINPUTDTO_H
