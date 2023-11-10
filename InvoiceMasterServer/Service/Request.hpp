#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {

    struct RequestStructure {
        char command;
        std::vector<std::string> arguments{};
    };


    class Request {
    private:
        std::string _requestText;
        void parse();
    public:
        explicit Request(std::string& requestText);
        std::unique_ptr<RequestStructure> parsed;
        bool isValidCommand (std::string& code);
        bool isValidArgument (std::string& item);

    };

} // InvoiceMasterServer
