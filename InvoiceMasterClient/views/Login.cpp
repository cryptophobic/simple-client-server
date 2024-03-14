#include "Login.hpp"
#include "config/settings.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterClient {

    std::string Login::buildRequest(const char requestCommand, const std::vector<std::string>& arguments)
    {
        return protocol::Request::build({requestCommand, arguments});
    }

    std::unique_ptr<CommandStruct> Login::run()
    {
        std::vector<std::string> arguments{};
        std::string login;
        std::string pass;

        context->userOutputSystem->outputLine("Please enter your login");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(login);
        arguments.emplace_back(login);
        context->userOutputSystem->outputLine("Please enter your password");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(pass);
        arguments.emplace_back(pass);

        auto command = std::make_unique<CommandStruct>();
        command->request = buildRequest(protocol::requestLogin, arguments);

        return command;
    }
} // InvoiceMasterClient
