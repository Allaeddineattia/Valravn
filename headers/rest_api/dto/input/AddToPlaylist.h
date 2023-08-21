//
// Created by alro on 8‏/5‏/2021.
//

#ifndef VALRAVEN_ADDTOPLAYLIST_H
#define VALRAVEN_ADDTOPLAYLIST_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp-swagger/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"

class PlayMediaDto : public oatpp::DTO {

    DTO_INIT(PlayMediaDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, mimeType);

};

class PlayListItem : public oatpp::DTO {

    DTO_INIT(PlayListItem, DTO)

    DTO_FIELD(Int32, mediaId);
    DTO_FIELD(Int32, position);
    DTO_FIELD(String, mimeType);

};

class AddMediaToPlaylist : public oatpp::DTO {

    DTO_INIT(AddMediaToPlaylist, DTO)
    DTO_FIELD(Int32, size);
    DTO_FIELD(List<oatpp::Object<PlayListItem>>, medias);

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"

#endif //VALRAVEN_ADDTOPLAYLIST_H
