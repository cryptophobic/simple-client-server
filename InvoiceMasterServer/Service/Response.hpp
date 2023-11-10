#pragma once

#include <string>
#include <vector>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {

    class Response {
    private:
        char _responseCode;
        std::string _responseBody;
    public:
        Response() : _responseCode(settings::responseError) {};
        Response(char responseCode, const std::string& responseBody);
        std::vector<std::string> getParsed();
    };

} // InvoiceMasterServer
