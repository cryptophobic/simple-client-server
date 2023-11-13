#include "Response.hpp"
#include <sstream>
#include <iostream>

namespace InvoiceMasterClient {

    Response::Response(std::string &responseText) : _responseText(responseText)
    {
        parsed = std::make_unique<ResponseStructure>();
        parse();
    }


    void Response::parse()
    {
        std::string responseItem;
        std::stringstream ss(_responseText);

        try {
            std::getline(ss, responseItem, settings::delimiter);
            parseAndValidateResponseCode(responseItem);
            std::getline(ss, responseItem, settings::delimiter);
            parseAndValidateAuthorizedSection(responseItem);
            while (getline(ss, responseItem, settings::delimiter)) {
                parseAndValidateBody(responseItem);
            }
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Response::parseAndValidateResponseCode(std::string& code) const
    {
        if (code.length() == 1 && settings::responseCodes.contains(code[0])) {
            parsed->responseCode = code[0];
            if (parsed->responseCode == settings::responseSuccess) {
                std::cout << "Success!" << std::endl;
            } else {
                std::cout << "Error" << std::endl;
            }
            return;
        }
        throw std::invalid_argument("parseAndValidateResponseCode: Corrupted message");
    }

    void Response::parseAndValidateAuthorizedSection(std::string& code) const
    {
        if (code.length() == 1 && settings::authorizedCodes.contains(code[0])) {
            parsed->disconnected = code[0] == settings::disconnected;
            parsed->isAuthorized = code[0] == settings::authorized;
            if (parsed->isAuthorized) {
                std::cout << "Authorized!" << std::endl;
            } else {
                std::cout << "Not Authorized" << std::endl;
            }
            if (parsed->disconnected) {
                std::cout << "Disconnected!" << std::endl;
            }
            return;
        }
        throw std::invalid_argument("parseAndValidateAuthorizedSection: Corrupted message");
    }

    void Response::parseAndValidateBody(std::string& item) const
    {
        parsed->body.emplace_back(item);
    }

} // InvoiceMasterClient
