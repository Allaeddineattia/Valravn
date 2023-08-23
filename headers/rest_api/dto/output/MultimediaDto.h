//
// Created by alro on 16‏/1‏/2021.
//

#ifndef VALRAVEN_MULTIMEDIADTO_H
#define VALRAVEN_MULTIMEDIADTO_H

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include <media_player/Multimedia.h>

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"

class MultimediaDto : public oatpp::DTO {

    DTO_INIT(MultimediaDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, path);
    DTO_FIELD(UInt64 , size);
    DTO_FIELD(String, mimeType);


public:

    static Object<MultimediaDto> createDtoFromEntity(const Multimedia & multimedia){
        Object<MultimediaDto> dto = Object<MultimediaDto>::createShared();
        dto->id = multimedia.get_id();
        dto->path = multimedia.getPath().data();
        dto->size = multimedia.getSize();
        dto->mimeType = multimedia.getMimeType().data();
        return dto;
    }

};


#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //VALRAVEN_MULTIMEDIADTO_H
