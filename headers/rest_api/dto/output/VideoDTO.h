//
// Created by alro on 18‏/4‏/2021.
//

#ifndef VALRAVEN_VIDEODTO_H
#define VALRAVEN_VIDEODTO_H


#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include <video/Video.h>
#include "MultimediaDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"


class VideoDTO : public oatpp::DTO {

    DTO_INIT(VideoDTO, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, resolution);
    DTO_FIELD(Int32, duration);
    DTO_FIELD(Object<MultimediaDto> , mulitmedia);


public:
    static Object<VideoDTO> createDtoFromEntity(const Video & video){
        Object<VideoDTO> dto = Object<VideoDTO>::createShared();
        dto->id = video.get_id();
        dto->resolution = video.getResolution().data();
        dto->duration = video.getDuration();
        dto->mulitmedia = MultimediaDto::createDtoFromEntity(video.getMultimedia());
        return dto;
    }

    static oatpp::List<oatpp::Object<VideoDTO>> createDtoVectorFromEntities(vector<unique_ptr<Video>> videos){
        oatpp::List<oatpp::Object<VideoDTO>> listOfDto = oatpp::List<oatpp::Object<VideoDTO>>::createShared();
        for (const auto & video : videos){
            if(video){
                Object<VideoDTO> dto = createDtoFromEntity(*video);
                listOfDto->push_back(dto);
            }
        }
        return listOfDto;
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"
#endif //VALRAVEN_VIDEODTO_H
