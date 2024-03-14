#include <sstream>
#include <vector>
#include "protocol/Response.hpp"
#include "protocol/ApiAccess.hpp"
#include "StringHelper.hpp"
#include "security/Sha2Wrapper.hpp"

namespace protocol {

    std::unique_ptr<ResponseStructure> Response::parse(const std::string &responseText)
    {
        std::vector<std::string> responseItems{};
        std::stringstream ss(responseText);
        auto parsedResponse = std::make_unique<ResponseStructure>();

        helpers::StringHelper::splitQuoted(responseText, delimiter, responseItems, true);
        validateResponseItems(responseItems);

        parsedResponse->responseCode = responseItems[RESPONSE_CODE_OFFSET][0];
        parsedResponse->connectionStatus = responseItems[CONNECTION_STATUS_OFFSET][0];
        parsedResponse->authorized = responseItems[AUTHORIZATION_STATUS_OFFSET][0];
        parsedResponse->licenceStatus = responseItems[LICENCE_STATUS_OFFSET][0];
        parsedResponse->body = responseItems[BODY_OFFSET];

        return parsedResponse;
    }

    std::string Response::build(const ResponseStructure &response) {
        std::vector<std::string> chunks{};
        std::string responseString{};
        std::vector<std::string> buffer{RESPONSE_ITEMS_MIN_SIZE};

        auto checksum = calculateCheckSum(response.body);

        buffer[RESPONSE_CODE_OFFSET]        = response.responseCode;
        buffer[CONNECTION_STATUS_OFFSET]    = response.connectionStatus;
        buffer[AUTHORIZATION_STATUS_OFFSET] = response.authorized;
        buffer[LICENCE_STATUS_OFFSET]       = response.licenceStatus;
        buffer[CHECKSUM_OFFSET]             = checksum;
        buffer[BODY_OFFSET]                 = response.body;

        helpers::StringHelper::join(buffer, delimiter, responseString, true);
        responseString += terminateChar;

        return responseString;
    }

    void Response::validateResponseItems(const std::vector<std::string> &responseItems) {
        if (responseItems.size() < RESPONSE_ITEMS_MIN_SIZE) {
            throw std::invalid_argument("protocol::validateResponseItems: Invalid response size");
        }
        Agreements::validateResponseCode(responseItems[RESPONSE_CODE_OFFSET]);
        Agreements::validateConnectionStatus(responseItems[CONNECTION_STATUS_OFFSET]);
        Agreements::validateAuthorizedCode(responseItems[AUTHORIZATION_STATUS_OFFSET]);
        Agreements::validateLicenceStatus(responseItems[LICENCE_STATUS_OFFSET]);

        validateCheckSum(responseItems[BODY_OFFSET], responseItems[CHECKSUM_OFFSET]);
    }

    std::string Response::calculateCheckSum(const std::string &content) {
        security::Sha2Wrapper sha2Wrapper;
        std::string sha2Checksum;
        sha2Wrapper.hashString(content, sha2Checksum);
        return sha2Checksum;
    }

    void Response::validateCheckSum(const std::string& content, const std::string& sha2Checksum) {
        security::Sha2Wrapper sha2Wrapper;
        if (!sha2Wrapper.verify(content, sha2Checksum)) {
            throw std::invalid_argument("protocol::validateCheckSum: Invalid checksum");
        }
    }
} // protocol
