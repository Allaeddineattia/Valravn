//
// Created by alro on 16‏/1‏/2021.
//

#ifndef MYPROJECT_MULTIMEDIADTO_H
#define MYPROJECT_MULTIMEDIADTO_H
#include <Entity/Multimedia.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"

class MultimediaDto : public oatpp::DTO {

    DTO_INIT(MultimediaDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, path);
    DTO_FIELD(UInt64 , size);
    DTO_FIELD(String, mimeType);


public:
    static Object<MultimediaDto> createDtoFromEntity(const Multimedia & multimedia){
        auto dto = make_shared<MultimediaDto>();
        dto->id = multimedia.getId();
        dto->path = multimedia.getPath().data();
        dto->size = multimedia.getSize();
        dto->mimeType = multimedia.getMimeType().data();
        return Object<MultimediaDto>(dto);

    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //MYPROJECT_MULTIMEDIADTO_H
