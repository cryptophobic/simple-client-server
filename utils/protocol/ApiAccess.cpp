#include "protocol/ApiAccess.hpp"

namespace protocol {
    void ApiAccess::validateCommand(const std::string& command)
    {
        if (command.length() != 1) {
            throw std::invalid_argument("protocol::validateCommand: Invalid command");
        }
        validateCommand(command[0]);
    }

    void ApiAccess::validateCommand(char command)
    {
        if (!commands.contains(command)) {
            throw std::invalid_argument("protocol::validateCommand: Invalid command");
        }
    }

    void ApiAccess::validateArguments(char command, const std::vector<std::string>& arguments)
    {
        if (argumentsNumber.contains(command) && arguments.size() != argumentsNumber.at(command)) {
            throw std::invalid_argument("protocol::validateArguments: incorrect number of arguments");
        }
    }
}
