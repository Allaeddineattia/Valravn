//
// Created by alro on 16‏/1‏/2021.
//

#ifndef VALRAVEN_ERRORHANDLER_H
#define VALRAVEN_ERRORHANDLER_H



#include "rest_api/dto/StatusDto.h"

#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/web/protocol/http/outgoing/ResponseFactory.hpp"

class ErrorHandler : public oatpp::web::server::handler::ErrorHandler {
private:
    typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
    typedef oatpp::web::protocol::http::Status Status;
    typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
public:

    ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper)        : m_objectMapper(objectMapper){};

    std::shared_ptr<OutgoingResponse>
    handleError(const Status& status, const oatpp::String& message, const Headers& headers) override{

        auto error = StatusDto::createShared();
        error->status = "ERROR";
        error->code = status.code;
        error->message = message;

        auto response = ResponseFactory::createResponse(status, error, m_objectMapper);

        for(const auto& pair : headers.getAll()) {
            response->putHeader(pair.first.toString(), pair.second.toString());
        }

        return response;

    }


    virtual ~ErrorHandler()= default;
};


#endif //VALRAVEN_ERRORHANDLER_H
