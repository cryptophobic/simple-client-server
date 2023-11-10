#include "Response.hpp"
#include <sstream>
#include <iostream>

namespace InvoiceMasterClient {

    Response::Response(std::string &responseText) : _responseText(responseText)
    {
        parse();
    }


    void Response::parse()
    {
        std::string responseItem;
        parsed = std::make_unique<ResponseStructure>();

        std::stringstream ss(_responseText);

        std::getline(ss, responseItem, settings::delimiter);

        if (!isValidResponseCode(responseItem)) {
            parsed->responseCode = settings::responseCorruptedData;
            std::cerr << "Corrupted message" << std::endl;
            return;
        }
        parsed->responseCode = responseItem[0];
        if (parsed->responseCode == settings::responseSuccess) {
            std::cout << "Success!" << std::endl;
        } else {
            std::cout << "Error" << std::endl;
        }
        while (getline(ss, responseItem, settings::delimiter)) {
            if (isValidResponseItem(responseItem)) {
                parsed->body.emplace_back(responseItem);
            }
        }
    }

    bool Response::isValidResponseCode (std::string& code)
    {
        return code.length() == 1 && settings::responseCodes.contains(code[0]);
    }

    bool Response::isValidResponseItem (std::string& item)
    {
        //TODO: validation implementation
        return true;
    }
} // InvoiceMasterClient
