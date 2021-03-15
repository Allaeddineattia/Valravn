//
// Created by alro on 17‏/1‏/2021.
//

#ifndef MYPROJECT_MULTIMEDIAINPUTDTO_H
#define MYPROJECT_MULTIMEDIAINPUTDTO_H
#include <Entity/Multimedia.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)"oatpp/codegen/DTO_define.hpp"

class MultimediaInputDto : public oatpp::DTO {

    DTO_INIT(MultimediaInputDto, DTO)

    DTO_FIELD(String, path);
    DTO_FIELD(UInt64 , size);
    DTO_FIELD(String, mimeType);


public:
    std::unique_ptr<Multimedia> createEntityFromDto(){
        return make_unique<Multimedia>(0, this->path->c_str(), this->size, this->mimeType->c_str());
    }

};

#include OATPP_CODEGEN_END(DTO)"oatpp/codegen/DTO_undef.hpp"
#endif //MYPROJECT_MULTIMEDIAINPUTDTO_H
