#pragma once

#include <string>
#include <vector>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {

    class Response {
    private:
        char _responseCode;
        char _authorized;
        std::string _responseBody;
    public:
        Response() : _responseCode(settings::responseError) {};
        Response(char responseCode, char authorized, const std::string& responseBody);
        std::vector<std::string> getParsed();
    };

} // InvoiceMasterServer
