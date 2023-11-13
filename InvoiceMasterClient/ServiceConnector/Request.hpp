#pragma once

#include "../../settings/ServiceList.hpp"
#include <vector>
#include <string>

namespace InvoiceMasterClient {

    class Request {
    private:
        settings::ServiceSignature _command;
        std::vector<std::string> _arguments;

    public:
        explicit Request(settings::ServiceSignature command, std::vector<std::string> arguments)
            : _arguments(std::move(arguments)), _command(command)
        {};

        std::vector<std::string> getParsed();
    };
}