//
// Created by alro on 17‏/1‏/2021.
//

#ifndef MYPROJECT_MULTIMEDIAINPUTDTO_H
#define MYPROJECT_MULTIMEDIAINPUTDTO_H
#include <Entity/Contract/Multimedia.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"

class MultimediaInputDto : public oatpp::DTO {

    DTO_INIT(MultimediaInputDto, DTO)

    DTO_FIELD(String, path)= "";
    DTO_FIELD(UInt64 , size) = (0,0);
    DTO_FIELD(String, mimeType)= "";


public:
    std::unique_ptr<Multimedia> createEntityFromDto(){
        unsigned int newId = Multimedia::generateNewId();
        return make_unique<Multimedia>(newId , this->path->c_str(), this->size, this->mimeType->c_str());
    }

    std::unique_ptr<Multimedia> updateEntityFromDto(int entity_id){
        auto multimedia = Multimedia::fetch_by_id(entity_id);
        auto newPath = this->path ? this->path->c_str() : multimedia->getPath().data();

        return make_unique<Multimedia>(entity_id , newPath, this->size, this->mimeType->c_str());
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"
#endif //MYPROJECT_MULTIMEDIAINPUTDTO_H
