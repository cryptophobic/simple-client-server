#include "protocol/Request.hpp"
#include "protocol/Agreements.hpp"
#include "protocol/ApiAccess.hpp"
#include "StringHelper.hpp"

namespace protocol {

    std::string Request::build(const RequestStructure &request) {
        std::vector<std::string> buffer{1};

        std::string requestString{};
        ApiAccess::validateCommand(request.command);
        buffer[REQUEST_COMMAND_OFFSET] = request.command;

        ApiAccess::validateArguments(request.command, request.arguments);
        buffer.insert(buffer.end(), request.arguments.begin(), request.arguments.end());

        helpers::StringHelper::join(buffer, delimiter, requestString, true);
        requestString += terminateChar;

        return requestString;
    }

    std::unique_ptr<RequestStructure> Request::parse(const std::string &requestText) {
        std::vector<std::string> requestItems{};

        auto parsedRequest = std::make_unique<RequestStructure>();
        helpers::StringHelper::splitQuoted(requestText, delimiter, requestItems, true);

        validateRequestItems(requestItems);
        ApiAccess::validateCommand(requestItems[REQUEST_COMMAND_OFFSET]);

        //convert string to char
        parsedRequest->command = requestItems[REQUEST_COMMAND_OFFSET][0];

        // if there are arguments
        if (requestItems.size() > 1) {
            parsedRequest->arguments.insert(parsedRequest->arguments.end(), requestItems.begin() + 1, requestItems.end());
        }

        ApiAccess::validateArguments(parsedRequest->command, parsedRequest->arguments);
        return parsedRequest;
    }

    void Request::validateRequestItems(const std::vector<std::string>& requestItems) {
        if (requestItems.empty()) {
            throw std::invalid_argument("protocol::validateRequestItems: Invalid request size");
        }
    }

} // protocol
