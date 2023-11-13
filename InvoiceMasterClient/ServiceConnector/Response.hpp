#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterClient {

    struct ResponseStructure {
        char responseCode = settings::responseCorruptedData;
        bool isAuthorized = false;
        bool disconnected = false;
        std::vector<std::string> body{};
    };

    class Response {
    private:
        const std::string _responseText;
        void parseAndValidateResponseCode(std::string& code) const;
        void parseAndValidateAuthorizedSection(std::string& code) const;
        void parseAndValidateBody(std::string& code) const;

        void parse();

    public:
        explicit Response(std::string& responseText);
        std::unique_ptr<ResponseStructure> parsed;

    };

} // InvoiceMasterClient
