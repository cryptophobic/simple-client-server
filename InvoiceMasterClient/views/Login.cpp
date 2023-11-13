#include "Login.hpp"

#include <iostream>
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> Login::run()
    {
        std::vector<std::string> arguments{settings::services.login.argumentsNumber, ""};

        std::cout << "Please enter your login and password separated by space" << std::endl;
        std::cout << ":> ";

        for (auto & argument: arguments) {
            std::cin >> argument;
        }

        std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();
        command->request = std::make_unique<Request>(settings::services.login, arguments);

        return std::move(command);
    }
} // InvoiceMasterClient
