#pragma once
#include <vector>
#include <string>
#include <memory>

namespace protocol {

    constexpr unsigned char REQUEST_COMMAND_OFFSET  = 0;
    constexpr unsigned char REQUEST_ARGUMENTS_OFFSET = 1;

    struct RequestStructure {
        char command;
        std::vector<std::string> arguments{};
    };

    class Request {
    public:
        static std::unique_ptr<RequestStructure> parse(const std::string& requestText);
        static std::string build(const RequestStructure &request);
    protected:
        static void validateRequestItems(const std::vector<std::string> &responseItems);
    };

} // protocol
