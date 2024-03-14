#pragma once

#include "Agreements.hpp"
#include <vector>
#include <string>
#include <memory>

namespace protocol {

    constexpr unsigned char RESPONSE_CODE_OFFSET         = 0;
    constexpr unsigned char CONNECTION_STATUS_OFFSET     = 1;
    constexpr unsigned char AUTHORIZATION_STATUS_OFFSET  = 2;
    constexpr unsigned char LICENCE_STATUS_OFFSET        = 3;
    constexpr unsigned char CHECKSUM_OFFSET              = 4;
    constexpr unsigned char BODY_OFFSET                  = 5;
    constexpr unsigned char RESPONSE_ITEMS_MIN_SIZE      = 6;

    struct ResponseStructure {
        char responseCode     = responseCorruptedData;
        char authorized       = notAuthorized;
        char connectionStatus = disconnected;
        char licenceStatus    = licenceNotConfirmed;
        std::string body{};
    };

    class Response {
    public:
        static std::unique_ptr<ResponseStructure> parse(const std::string& responseText);
        static std::string build(const ResponseStructure &response);
    protected:
        static void validateResponseItems(const std::vector<std::string>& responseItems);
        static void validateCheckSum(const std::string& content, const std::string& sha2Checksum);
        static std::string calculateCheckSum(const std::string& content);
    };

} // protocol
