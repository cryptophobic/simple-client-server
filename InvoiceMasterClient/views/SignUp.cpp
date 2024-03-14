#include "SignUp.hpp"
#include "config/settings.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> SignUp::run()
    {
        std::vector<std::string> arguments{};
        std::string login;
        std::string pass, confirm;

        context->userOutputSystem->outputLine("Please enter your new account name");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(login);
        arguments.emplace_back(login);
        context->userOutputSystem->outputLine("Please enter your password");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(pass);
        context->userOutputSystem->outputLine("Please confirm your password");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(confirm);
        if (pass != confirm) {
            throw std::invalid_argument("Passwords do not match");
        }

        arguments.emplace_back(pass);

        auto command = std::make_unique<CommandStruct>();
        command->request = protocol::Request::build({protocol::requestSignUp, arguments});

        return command;
    }
} // InvoiceMasterClient
