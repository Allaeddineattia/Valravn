//
// Created by alro on 17‏/1‏/2021.
//

#ifndef VALRAVEN_MEDIAUPLOADDTO_H
#define VALRAVEN_MEDIAUPLOADDTO_H


#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp-swagger/Types.hpp>

#include <image/Image.h>
#include <video/Video.h>
#include "MultimediaInputDto.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class MediaUploadDto : public oatpp::DTO {

    DTO_INIT(MediaUploadDto, DTO)

   // DTO_FIELD(Object<MultimediaInputDto> , mulitmedia);
    DTO_FIELD(oatpp::swagger::Binary , file);
    DTO_FIELD(String, resolution) = "";


public:
    static unique_ptr<Image> createImageFromDto (string_view _path, string_view _type, string_view _resolution, unsigned int _size){
        unsigned int newImageId = Image::generate_new_id();
        unsigned int newMultimediaId = Multimedia::generate_new_id();
        unique_ptr<Multimedia> multimedia = make_unique<Multimedia>(newMultimediaId , _path, _size, _type);
        return make_unique<Image>(newImageId, _resolution, std::move(multimedia));
    }

    static unique_ptr<Video> createVideoFromDto (string_view _path, string_view _type, string_view _resolution, unsigned int _size, int _duration){
        unsigned int newVideoId = Video::generate_new_id();
        unsigned int newMultimediaId = Multimedia::generate_new_id();
        unique_ptr<Multimedia> multimedia = make_unique<Multimedia>(newMultimediaId , _path, _size, _type);
        return make_unique<Video>(newVideoId, _duration, std::move(multimedia), _resolution);
    }

};

#include OATPP_CODEGEN_END(DTO)

#endif //VALRAVEN_MEDIAUPLOADDTO_H
