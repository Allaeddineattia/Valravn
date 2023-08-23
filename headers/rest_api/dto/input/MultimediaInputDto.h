//
// Created by alro on 17‏/1‏/2021.
//

#ifndef VALRAVEN_MULTIMEDIAINPUTDTO_H
#define VALRAVEN_MULTIMEDIAINPUTDTO_H

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include <media_player/Multimedia.h>

#include OATPP_CODEGEN_BEGIN(DTO)

class MultimediaInputDto : public oatpp::DTO {

    DTO_INIT(MultimediaInputDto, DTO)

    DTO_FIELD(String, path)= "";
    DTO_FIELD(UInt64 , size) = (0,0);
    DTO_FIELD(String, mimeType)= "";


public:
    std::unique_ptr<Multimedia> createEntityFromDto(){
        unsigned int newId = Multimedia::generate_new_id();
        return make_unique<Multimedia>(newId , this->path->c_str(), this->size, this->mimeType->c_str());
    }

    std::unique_ptr<Multimedia> updateEntityFromDto(int entity_id){
        std::unique_ptr<Multimedia> multimedia = Multimedia::fetch_by_id(entity_id);
        string newPath = this->path ? this->path->c_str() : multimedia->getPath().data();
        return make_unique<Multimedia>(entity_id , newPath, this->size, this->mimeType->c_str());
    }

};

#include OATPP_CODEGEN_END(DTO)
#endif //VALRAVEN_MULTIMEDIAINPUTDTO_H
