#pragma once

#include "../../settings/ServiceList.hpp"
#include <vector>
#include <string>

namespace InvoiceMasterClient {

    class Request {
    private:
        settings::ServiceSignature _command;
        const std::vector<std::string>& _arguments;

    public:
        Request(settings::ServiceSignature command, const std::vector<std::string>& arguments)
            : _arguments(arguments), _command(command)
        {};

        std::vector<std::string> getParsed();
    };
}