//
// Created by alro on 16‏/1‏/2021.
//

#ifndef MYPROJECT_STATUSDTO_H
#define MYPROJECT_STATUSDTO_H
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <string_view>

#include OATPP_CODEGEN_BEGIN(DTO)

class StatusDto : public oatpp::DTO {

    DTO_INIT(StatusDto, DTO)

    DTO_FIELD_INFO(status) {
            info->description = "Short status text";
    }
    DTO_FIELD(String, status);

    DTO_FIELD_INFO(code) {
            info->description = "Status code";
    }
    DTO_FIELD(Int32, code);

    DTO_FIELD_INFO(message) {
            info->description = "Verbose message";
    }
    DTO_FIELD(String, message);

public:
    static Object<StatusDto> ok(std::string_view message){
        auto status = StatusDto::createShared();
        status->status = "OK";
        status->code = 200;
        status->message = message.data();
        return status;
    }

};

#include OATPP_CODEGEN_END(DTO)



#endif //MYPROJECT_STATUSDTO_H
