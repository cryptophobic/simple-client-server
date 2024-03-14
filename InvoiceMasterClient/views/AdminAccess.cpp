#include <iostream>
#include <memory>
#include "AdminAccess.hpp"
#include "protocol/ApiAccess.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> AdminAccess::run()
    {
        char choice;
        context->userOutputSystem->outputLine("0. Main menu");
        context->userOutputSystem->outputLine("1. Server shut down");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);
        auto command = std::make_unique<CommandStruct>();

        switch (choice) {
            case '0':
                return command;
            case '1': {
                command->internalCommand = protocol::requestDisconnect;
                command->request = protocol::Request::build({
                    protocol::requestAdminAccess,
                    std::vector<std::string>{"quit"}});

                return command;
            }
            default: {
                context->userOutputSystem->outputLine("Incorrect input");
                command->internalCommand = protocol::requestAdminAccess;
                return command;
            }
        }
    }
} // InvoiceMasterClient
