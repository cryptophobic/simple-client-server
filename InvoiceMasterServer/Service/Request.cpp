#include "Request.hpp"
#include "../../settings/ServiceList.hpp"
#include <memory>
#include <sstream>

namespace InvoiceMasterServer {

    Request::Request(std::string& requestText) : _requestText(requestText)
    {
        parse();
    }

    void Request::parse()
    {
        std::string responseItem;
        parsed = std::make_unique<RequestStructure>();

        std::stringstream ss(_requestText);

        std::getline(ss, responseItem, settings::delimiter);

        if (!isValidCommand(responseItem)) {
            parsed->command = settings::responseCorruptedData;
            return;
        }
        parsed->command = responseItem[0];
        while (getline(ss, responseItem, settings::delimiter)) {
            if (isValidArgument(responseItem)) {
                parsed->arguments.emplace_back(responseItem);
            }
        }
    }

    bool Request::isValidCommand (std::string& code)
    {
        return code.length() == 1 && settings::commands.contains(code[0]);
    }

    bool Request::isValidArgument (std::string& item)
    {
        //TODO: validation implementation
        return true;
    }
} // InvoiceMasterServer
