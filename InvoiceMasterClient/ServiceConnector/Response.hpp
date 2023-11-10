#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterClient {

    struct ResponseStructure {
        char responseCode;
        std::vector<std::string> body{};
    };

    class Response {
    private:
        const std::string _responseText;
        bool isValidResponseCode (std::string& code);
        bool isValidResponseItem (std::string& item);
        void parse();

    public:
        explicit Response(std::string& responseText);
        std::unique_ptr<ResponseStructure> parsed;

    };

} // InvoiceMasterClient
